#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <optional>

class Tokenizer {
    public:
        Tokenizer(std::string &input)
            : m_input { input } {}
        std::optional<std::string_view> next(){
            auto view = std::string_view(m_input);

            while(m_index < m_input.length()){
                char c = m_input.at(m_index);

                switch(c){
                    case ' ':
                    case '\t':
                    case '\n':
                    case ',':
                        break;
                    case '~': {
                        if (m_index + 1 < m_input.length() && m_input.at(m_index + 1) == '@')
                            return view.substr(m_index++, 2);
                        return view.substr(m_index, 1);
                    }
                    case '[':
                    case ']':
                    case '{':
                    case '}':
                    case '(':
                    case ')':
                    case '\'':
                    case '`':
                    case '^':
                    case '@':
                        return view.substr(m_index, 1);
                    case '"': {
                        size_t start = m_index;
                        ++m_index;
                        while(m_index < m_input.length()){
                            c = m_input.at(m_index);
                            switch(c) {
                                case '"':
                                    return view.substr(start, m_input.length() - m_index);
                                case '\\':
                                    ++m_index;
                                    break;
                            }
                            ++m_index;
                        }
                        std::cout << "EOF\n";
                        return view.substr(start, m_input.length() - m_index);
                    }
                    case ';': {
                        size_t start = m_index;
                        while(m_index < m_input.length()){
                            c = m_input.at(m_index);
                            if (c == '\n')
                                break;
                            ++m_index;
                        }
                        return view.substr(start, m_input.length() - m_index);
                    }
                    default: {
                        size_t start = m_index;
                        bool done = false;
                        while(!done && m_index < m_input.length()){
                            c = m_input.at(m_index);
                            switch (c) {
                                case ' ':
                                case '\t':
                                case '\n':
                                case '[':
                                case ']':
                                case '{':
                                case '}':
                                case '(':
                                case ')':
                                case '\'':
                                case '"':
                                case '`':
                                case ',':
                                case ';':
                                    done = true;
                                    break;
                            }
                            ++m_index;
                        }
                        return view.substr(start, m_input.length() - m_index);
                    }
                }
                ++m_index;
            }

            return {};
        }
    private:
        std::string &m_input;
        size_t m_index { 0 };
};

/*
Value *read_str(std::string &input){
    //TODO: tokenize, parse into an AST, return the AST
}
*/