/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:51:25 by vpeinado          #+#    #+#             */
/*   Updated: 2024/10/02 15:25:35 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Join_HPP
#define Join_HPP

#include "ACommand.hpp"
#include "Server.hpp"

class Join : public ACommand
{
    private:
    
        /*** Orthodox Canonical Form ***/
        
        Join(const Join &src);
        Join &operator=(const Join &src);
        Join();
        
    public:
        
        /*** Orthodox Canonical Form ***/
        
        Join(Server &server);
        ~Join();

        /*** MEMBER FUNCTIONS ***/
        
        int validArgs(std::vector<std::string> args, int fdClient);
        void run(std::vector<std::string> args, int fdClient);
    
};

#endif