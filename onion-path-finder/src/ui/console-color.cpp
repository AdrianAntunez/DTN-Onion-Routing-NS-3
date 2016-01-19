/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file console-color.cpp
 * @author Rubén Martínez - <rmartinez@deic.uab.cat>
 * @date Created on: 14/1/2016
 * @brief ConsoleColor
 */

#include "console-color.h"
/*
const std::map <ConsoleColor::Colors,ConsoleColor::ColorCode>  ConsoleColor::m_consoleCodes =
{
   {ConsoleColor::Colors::Green, {std::string("\033[2;32m"),std::string("\033[0m")}},
   {UserInterface::FlagTypes::SourceFlag, {std::string("source"),'s', std::string("Source node for path exploration")}},
   {UserInterface::FlagTypes::DestinationFlag, { std::string("destination"),'d', std::string("Destination node of path exploration")}}
};
*/
ConsoleColor::ConsoleColor()
{
}

ConsoleColor::ConsoleColor(Colors c, FontStyle style, std::string text):
    m_color(c),
    m_style(style),
    m_text(text)
{

}
ConsoleColor::Colors ConsoleColor::color() const
{
    return m_color;
}

void ConsoleColor::setColor(const Colors &value)
{
    m_color = value;
}

std::string ConsoleColor::text() const
{
   return m_text;
}

void ConsoleColor::setText(const std::string &text)
{
   m_text = text;
}

std::ostream& operator<<(std::ostream &os, const ConsoleColor &obj)
{
    os << std::string("\x1b[3") << std::to_string(obj.color());
    os << std::string((obj.style() == ConsoleColor::FontStyle::Normal) ? "m" : ";1m");
    os << obj.text();
    os <<  std::string("\x1b[0m");
    return os;
}

ConsoleColor::FontStyle ConsoleColor::style() const
{
    return m_style;
}

void ConsoleColor::setStyle(const FontStyle &style)
{
    m_style = style;
}




