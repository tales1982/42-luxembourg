# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Hello.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/24 18:05:23 by tales             #+#    #+#              #
#    Updated: 2026/04/24 18:39:49 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ft_list  = ["Hello", "tata!"]
ft_tuple = ("Hello", "toto!")
ft_set   = {"Hello", "tutu!"}
ft_dict  = {"Hello" : "titi!"}

#your code here

# Lista: acede ao índice 1 e substitui o valor diretamente
ft_list[1] = "World!"

# Tupla: imutável, então cria-se uma nova tupla com o mesmo nome
ft_tuple = (ft_tuple[0], "Luxembourg!")

# Set: sem índices, remove o valor antigo e adiciona o novo
ft_set.discard("tutu!")
ft_set.add("Hosingem!")

# Dicionário: usa a chave "Hello" para substituir o valor
ft_dict["Hello"] = "42Luxembourg!"


print(ft_list)
print(ft_tuple)
print(ft_set)
print(ft_dict)