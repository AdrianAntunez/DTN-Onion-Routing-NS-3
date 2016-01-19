/**
 * @copyright
 * Copyright (C) 2016 Universitat Autònoma de Barcelona
 * Department of Information and Communications Engineering
 * @file console-color.h
 * @author Rubén Martínez - <rmartinez@deic.uab.cat>
 * @date Created on: 14/1/2016
 * @brief ConsoleColor
 */

#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#include <string>

/**
 * @brief The ConsoleColor class offers FontStyle and Color printing.
 */
class ConsoleColor
{
public:

    enum Colors { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White };
    enum FontStyle { Normal, Bold };

    /**
     * @brief ConsoleColor default constructor
     */
    ConsoleColor();    
    /**
     * @brief ConsoleColor parametized constructor
     * @param c color
     * @param style style
     * @param text text
     */
    ConsoleColor(Colors c, FontStyle style, std::string text);

    /**
     * @brief Get color
     * @return color
     */
    Colors color() const;
    /**
     * @brief setColor
     * @param value
     */
    void setColor(const Colors &value);

    /**
     * @brief get style
     * @return style
     */
    FontStyle style() const;
    /**
     * @brief setStyle
     * @param style
     */
    void setStyle(const FontStyle &style);

    /**
     * @brief get text
     * @return text
     */
    std::string text() const;
    /**
     * @brief setText
     * @param text
     */
    void setText(const std::string &text);

private:
    /**
     * @brief m_color
     */
    Colors m_color;
    /**
     * @brief m_style
     */
    FontStyle m_style;
    /**
     * @brief m_text
     */
    std::string m_text;

};

std::ostream& operator<<(std::ostream& os, const ConsoleColor& obj );

#endif // CONSOLECOLOR_H
