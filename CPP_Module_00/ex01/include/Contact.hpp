/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:55:46 by tales             #+#    #+#             */
/*   Updated: 2024/11/08 12:21:50 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
public:
    Contact();
    ~Contact();

    void setAllInfo(const std::string &firstName, const std::string &lastName,
                    const std::string &nickName, const std::string &phoneNumber,
                    const std::string &darkestSecret);
    std::string getAllInfo() const;

private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickName;
    std::string _phoneNumber;
    std::string _darkestSecret;
};

#endif
