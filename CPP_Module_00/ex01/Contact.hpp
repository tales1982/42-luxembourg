/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 06:55:46 by tales             #+#    #+#             */
/*   Updated: 2024/11/12 14:06:38 by tlima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <limits>


class Contact {
public:
    Contact();
    ~Contact();

    void setAllInfo(const std::string &firstName, const std::string &lastName,
                    const std::string &nickName, const std::string &phoneNumber,
                    const std::string &darkestSecret);
    std::string getAllInfo() const;
    public:
    std::string getFirstName() const { return _firstName; }
    std::string getLastName() const { return _lastName; }
    std::string getNickName() const { return _nickName; }


private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickName;
    std::string _phoneNumber;
    std::string _darkestSecret;
};

#endif
