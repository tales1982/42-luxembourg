/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tales <tales@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:46:13 by sanweber          #+#    #+#             */
/*   Updated: 2025/02/24 10:40:07 by tales            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMATERIASOURCE_HPP
# define IMATERIASOURCE_HPP

# include <string>
# include "AMateria.hpp"

// Interface para a classe MateriaSource
class IMateriaSource
{
public:
    // Destrutor virtual para destruição adequada ao deletar objetos derivados
    virtual ~IMateriaSource() {}

    // Adiciona um modelo de AMateria à fonte de Materia
    virtual void learnMateria(AMateria* m) = 0;

    // Cria uma nova Materia com base no tipo fornecido
    virtual AMateria* createMateria(std::string const & type) = 0;
};

#endif
