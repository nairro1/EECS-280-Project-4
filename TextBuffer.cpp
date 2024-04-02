#include "TextBuffer.hpp"

TextBuffer::TextBuffer() : cursor(data.end()), row(1), column(0), index(0) {}

bool TextBuffer::forward()
{
    if (cursor != data.end())
    {
        if (*cursor == '\n')
        {
            ++row;
            column = 0;
        } 
        else
        {
            ++column;
        }
        ++cursor;
        ++index;
        return true;
    }
    return false;
}

bool TextBuffer::backward() {
    if (cursor != data.begin()) {
        // Save the current cursor position
        auto temp = cursor;
        
        // Move the cursor one character backward
        --temp;
        
        // Check if the character at the new cursor position is a newline
        if (*temp == '\n') {
            // Update row and column
            --row;
            column = compute_column();
        } else {
            // Update column
            --column;
        }

        // Update cursor and index
        cursor = temp;
        --index;

        return true;
    }
    return false;
}

void TextBuffer::insert(char c)
{
    if (cursor != data.end() && c != '\n')
    {
        data.insert(cursor, c);
        ++index;
        ++column;
    }
    else
    {
        data.insert(cursor, c);
        if (c == '\n')
        {
            ++row;
            column = 0;
        } 
        else
        {
            ++column;
        }
    }
}

bool TextBuffer::remove()
{
    if (cursor != data.end()) {
        auto temp = cursor; // Save current cursor position
        
        // Move cursor to the next character
        ++temp;
        
        // Check if the next character is a newline
        if (*temp == '\n') {
            --row; // Decrement row
            column = compute_column(); // Update column
        }
        cursor = data.erase(cursor);
        
        // Update index after removal
        index = std::distance(data.begin(), cursor);
        
        return true;
    }
    return false;
}

void TextBuffer::move_to_row_start()
{
    while (cursor != data.begin() && *cursor != '\n')
    {
        --cursor;
        --index;
    }
    column = 0;
}

void TextBuffer::move_to_row_end()
{
    while (cursor != data.end() && *cursor != '\n')
    {
        ++cursor;
        ++index;
        ++column;
    }
}

void TextBuffer::move_to_column(int new_column)
{
    // Handle case where new_column is less than 0
    if (new_column < 0)
    {
        move_to_row_start(); // Move to the start of the row (column 0)
        return;
    }

    // Get the current column
    int current_column = get_column();

    // Handle case where new_column is greater than current column
    if (new_column > current_column)
    {
        // Move forward until reaching the specified column
        while (current_column < new_column && cursor != data.end())
        {
            forward();
            ++current_column;
        }
    }
    // Handle case where new_column is less than current column
    else if (new_column < current_column)
    {
        // Move backward until reaching the specified column
        while (current_column > new_column && cursor != data.begin())
        {
            backward();
            --current_column;
        }
    }

    // Handle case where new_column is beyond the end of the row
    if (current_column < new_column)
    {
        move_to_row_end(); // Move to the end of the row
    }
}

bool TextBuffer::up()
{
    
    if (cursor == data.begin() && get_row() == 1)
    {
        // Cursor is already at the start of the buffer
        return false;
    }

    // Save the current cursor position
    auto temp = cursor;

    // Move cursor to the previous line
    while (temp != data.begin() && *temp != '\n')
    {
        --temp;
    }

    // If the cursor is not already at the first row
    if (temp != data.begin())
    {
        // Move cursor to the character after the newline
        --temp;
        cursor = temp;
        // Update the index
        index = std::distance(data.begin(), cursor);
        // Decrement the row
        --row;
        // Update the column position
        column = compute_column();

        return true;

    }

    // If cursor is already at the first row, return false
    return false;
}

bool TextBuffer::down()
{
    if (cursor == data.end())
    {
        // Cursor is already at the end, can't move down
        return false;
    }

    // Save the current cursor position
    auto temp = cursor;

    // Move cursor to the next line
    while (temp != data.end() && *temp != '\n')
    {
        ++temp;
    }
    ++temp;++temp;++temp;

    // If not already at the last row
    if (temp != data.end())
    {
        // Move cursor to the character after the newline
        ++temp;
        cursor = temp;

        // Update the index
        index = std::distance(data.begin(), cursor);

        // Update the column position
        column = compute_column();

        return true;
    }
    else
    {
        // If already at the last row, move cursor to the end
        cursor = temp;
        // Update the index
        index = std::distance(data.begin(), cursor);
       
        return true;
    }
}


bool TextBuffer::is_at_end() const
{
    return cursor == data.end();
}

char TextBuffer::data_at_cursor() const
{
    if (cursor != data.end())
    {
        return *cursor;
    }
    return '\0';
}

int TextBuffer::get_row() const
{
    return row;
}

int TextBuffer::get_column() const
{
    return column;
}

int TextBuffer::get_index() const {
    using const_iterator = decltype(data.begin()); // Define const_iterator type
    const_iterator constCursor = cursor; // Cast cursor to const_iterator
    return std::distance(data.begin(), constCursor);
}

int TextBuffer::size() const
{
    return data.size();
}

std::string TextBuffer::stringify() const
{
    std::string result;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        result += *it;
    }

    return result;
}

int TextBuffer::compute_column() const
{
    int count = 1; //changed from 0 to 1
    Iterator it = cursor;
    while (it != data.begin() && *it != '\n')
    {
        --it;
        ++count;
    }
    return count;
}