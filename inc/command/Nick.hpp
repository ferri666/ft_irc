/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:26:37 by vpeinado          #+#    #+#             */
/*   Updated: 2024/09/28 14:00:12 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
#define NICK_HPP

#include "ACommand.hpp"
#include "Server.hpp"

class Nick : public ACommand
{
    private:

        /*** Orthodox Canonical Form ***/
        
        Nick(const Nick &src);
        Nick &operator=(const Nick &src);
        Nick();
        
    public:
        
        /*** Orthodox Canonical Form ***/
        
        Nick(Server &server);
        ~Nick();

        /*** MEMBER FUNCTIONS ***/
        
        int validArgs(std::vector<std::string> args, int fdClient);
        void run(std::vector<std::string> args, int fdClient);  
            
};

#endif