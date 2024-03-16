local SyntaxHighlighter = {}
local SYNTAX_SCHEME = {
    ["KEYWORD"] = 2,
    ["FUNCTION"] = 2,
    ["NUMBER"] = 1,
    ["STRING"] = 1,
    ["COMMENT"] = 1,
    ["DEFAULT"] = 3
}
local KEYWORDS = {
    "function", "class", "super", "for", "do", "local", "while", "if", "then",
    "else", "elseif", "return", "continue", "break", "true", "false", "print",
    "begin", "end", "cls", "trace", "pset", "pget", "sget", "sset", "fget",
    "palt", "spr", "sspr", "fset", "mget", "mset", "peek", "poke", "peek4",
    "poke4", "peek2", "poke2", "circ", "circfill", "rect", "rectfill", "line",
    "flr", "sin", "cos", "rnd", "t", "time", "pairs", "ipairs", "in"
}
local TERMINATORS = {
    "\n", "{", "}", "(", ")", " ", "[", "]", ",", "=", ".", "*", "-", "+", "/",
    " "
}

function SyntaxHighlighter:clearColors() self.colors = {} end

function SyntaxHighlighter:setColor(lineIndex, index, color)
    if self.colors[lineIndex] == nil then self.colors[lineIndex] = {} end
    self.colors[lineIndex][index] = color
end

function SyntaxHighlighter:getColor(lineIndex, index)
    if self.colors[lineIndex] == nil then return SYNTAX_SCHEME.DEFAULT end
    return self.colors[lineIndex][index]
end

function SyntaxHighlighter:peek(line, index)
    if index > #line then return nil end
    return sub(line, index, index)
end

function SyntaxHighlighter:match(line, index, values, terminateValues)
    local found = true
    local resultIndex = nil

    for valueIndex = 1, #values do
        found = true
        for charIndex = 1, #values[valueIndex] do
            if self:peek(line, index + charIndex - 1) ~=
                self:peek(values[valueIndex], charIndex) then
                found = false
                break
            end
        end

        if found == true then
            local endIndex = index + #values[valueIndex]
            local nextChar = self:peek(line, endIndex)
            local prevChar = index > 1 and self:peek(line, index - 1) or nil

            -- Check for word boundaries
            if not (self:isWordCharacter(prevChar) or
                self:isWordCharacter(nextChar)) then
                return endIndex -- Include the last character in the keyword
            end
        end
    end

    return nil
end

function SyntaxHighlighter:isWordCharacter(char)
    return char and char:match("[%w_]")
end

function SyntaxHighlighter:isNumber(char, prevChar)
    -- Check if the character is a digit, but not part of a variable name
    -- A variable name part would be a digit following a letter or an underscore
    if char and char:match("%d") then
        if prevChar and (prevChar:match("[%a_]")) then
            return false -- Part of a variable name, not a standalone number
        else
            return true -- Standalone number or part of a number
        end
    end
    return false
end

function SyntaxHighlighter:highlightString(line, lineIndex, startIndex,
                                           quoteType)
    local i = startIndex
    repeat
        SyntaxHighlighter:setColor(lineIndex, i, SYNTAX_SCHEME.STRING)
        i = i + 1
        if i > #line then break end
    until sub(line, i, i) == quoteType
    SyntaxHighlighter:setColor(lineIndex, i, SYNTAX_SCHEME.STRING)
    return i + 1
end

function SyntaxHighlighter:highlightComment(line, lineIndex, startIndex)
    for i = startIndex, #line do
        SyntaxHighlighter:setColor(lineIndex, i, SYNTAX_SCHEME.COMMENT)
    end
    return #line + 1 -- Move to the end of the line
end

function SyntaxHighlighter:highlightKeyword(line, lineIndex, startIndex)
    local endIndex = self:match(line, startIndex, KEYWORDS, TERMINATORS)
    if endIndex then
        for i = startIndex, endIndex - 1 do
            SyntaxHighlighter:setColor(lineIndex, i, SYNTAX_SCHEME.KEYWORD)
        end
        return endIndex
    else
        -- If no keyword is found, move to the next character
        return startIndex + 1
    end
end

function SyntaxHighlighter:highlightNumber(line, lineIndex, startIndex)
    local i = startIndex
    while i <= #line and self:isNumber(sub(line, i, i), sub(line, i - 1, i - 1)) do
        SyntaxHighlighter:setColor(lineIndex, i, SYNTAX_SCHEME.NUMBER)
        i = i + 1
    end
    return i
end

function SyntaxHighlighter:highlightLine(line, lineIndex)
    local i = 1

    self.colors[lineIndex] = {}

    while i <= #line do
        local char = sub(line, i, i)
        local prevChar = i > 1 and sub(line, i - 1, i - 1) or nil

        -- String highlighting (double quotes)
        if char == "\"" then
            i = self:highlightString(line, lineIndex, i, "\"")

            -- String highlighting (single quotes)
        elseif char == "'" then
            i = self:highlightString(line, lineIndex, i, "'")

            -- Comment highlighting
        elseif char == "-" and self:peek(line, i + 1) == "-" then
            self:highlightComment(line, lineIndex, i)
            break

            -- Keyword highlighting
        elseif self:match(line, i, KEYWORDS, TERMINATORS) then
            i = self:highlightKeyword(line, lineIndex, i)

            -- Number highlighting
        elseif self:isNumber(char, prevChar) then
            i = self:highlightNumber(line, lineIndex, i)

            -- Default highlighting
        else
            self.colors[lineIndex][i] = SYNTAX_SCHEME.DEFAULT
            i = i + 1
        end
    end
end

function SyntaxHighlighter:cacheVisibleLines(textEditor)
    local lineHeight = 6 -- Height of each line of text
    local charWidth = 4 -- Width of each character

    -- Calculate the vertical offset to start drawing from, based on the scroll position.
    local startY = textEditor.y + textEditor.offsetY

    -- Determine the range of lines to draw, considering partial visibility.
    local firstLineIndex = math.max(1, math.floor(textEditor.scroll.y) + 1)
    local lastLineIndex = firstLineIndex + textEditor.rows_on_screen - 1

    -- Ensure we don't try to draw more lines than exist.
    lastLineIndex = math.min(lastLineIndex, #textEditor.lines)
    textEditor.drawLines = {}

    for lineIndex = firstLineIndex, lastLineIndex do
        local line = textEditor.lines[lineIndex] or ""
        local yOffset = (lineIndex - firstLineIndex) * lineHeight + startY
        local xPos = textEditor.x - textEditor.scroll.x * charWidth
        local drawText = ""
        local previousColor, previousBgColor = -1, -1

        for charIndex = 1, #line do
            local char = line:sub(charIndex, charIndex)
            local color = textEditor:getColor(lineIndex, charIndex)
            local bgColor = 0 -- Assume default background color for now

            -- Check if the character is part of a selection.
            if textEditor:isSelected(charIndex - 1, lineIndex - 1) then
                color = 3
                bgColor = 1
            elseif textEditor:isUnderCursor(charIndex - 1, lineIndex - 1) and
                    textEditor.cursor.visible then
                color = 3 -- Example cursor color
            end

            -- Insert color control codes before the character as needed.
            if charIndex == 1 or previousColor ~= color or previousBgColor ~= bgColor then
                if color ~= previousColor then
                    drawText = drawText .. chr(15) .. str(color)
                end
                if bgColor ~= previousBgColor then
                    drawText = drawText .. chr(14) .. str(bgColor)
                end
            end

            drawText = drawText .. char
            previousColor, previousBgColor = color, bgColor
        end

        textEditor.drawLines[#textEditor.drawLines + 1] = drawText
    end

end

return SyntaxHighlighter
