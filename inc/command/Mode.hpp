/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:42:53 by ffons-ti          #+#    #+#             */
/*   Updated: 2024/10/03 14:45:48 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
#define MODE_HPP

#include "ACommand.hpp"
#include "Server.hpp"

class Mode : public ACommand
{
    private:
        //Forma canonica no implementada
        Mode(const Mode &src);
        Mode &operator=(const Mode &src);
        Mode();
    public:
        Mode(Server &server);
        ~Mode();
        int validArgs(std::vector<std::string> args, int fdClient);
        void run(std::vector<std::string> args, int fdClient);      
};

#endif