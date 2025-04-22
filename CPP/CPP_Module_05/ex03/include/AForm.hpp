/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:29:45 by tlima-de          #+#    #+#             */
/*   Updated: 2025/04/22 13:06:37 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <stdexcept>
class Bureaucrat; 

const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN    = "\033[36m";
const std::string RESET   = "\033[0m";


class AForm {
    
    private:
    const std::string _name;
    bool _isSigned;
    const int _gradeToSign;
    const int _gradeToExecute;
    
    protected:
    std::string target;
    
    public:
        AForm(); // default
        AForm(const std::string &name, int gradeToSign, int gradeToExecute, const std::string &target);
        AForm(const AForm& other);
        AForm& operator=(const AForm& other);
        virtual ~AForm();
    
        std::string getName() const;
        bool isSigned() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        std::string getTarget() const;
    
        void beSigned(const Bureaucrat &bureaucrat);
        virtual void execute(Bureaucrat const & executor) const = 0;
    
        class GradeTooHighException : public std::exception {
            public: const char* what() const throw();
        };
        class GradeTooLowException : public std::exception {
            public: const char* what() const throw();
        };
    };
    
// Sobrecarga do operador <<
std::ostream& operator<<(std::ostream& out, const AForm& aform);

#endif