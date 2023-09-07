#pragma once

#include <string>

/// @brief Encloses the provided text with startDelim and endDelim.
/// @param text The text to enclose.
/// @param startDelim The character to prefix text with.
/// @param endDelim The character to suffix text with.
/// @return The altered string.
inline std::string enclose(const std::string& text, char startDelim, char endDelim)
{
    return std::string(startDelim + text + endDelim);
}

/// @brief Encloses the provided text with the designated character.
/// @param text The text to enclose.
/// @param delim The character to surround the text with. Passing from among
/// () [] {} <> will enclose the text with the appropriate closing character.
/// (e.g., enclose("hi", '<') will return "<hi>")
/// @return The string prefixed and suffixed by the delimiter.
inline std::string enclose(const std::string& text, char delim)
{
    switch (delim)
    {
    case '[':
    case ']':
        return enclose(text, '[', ']');

    case '(':
    case ')':
        return enclose(text, '(', ')');

    case '<':
    case '>':
        return enclose(text, '<', '>');

    case '{':
    case '}':
        return enclose(text, '{', '}');

    default:
        return enclose(text, delim, delim);
    }
}