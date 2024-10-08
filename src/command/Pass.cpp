/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpeinado <victor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:19:13 by vpeinado          #+#    #+#             */
/*   Updated: 2024/09/22 17:08:25 by vpeinado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

/******************************************************************************
* ------------------------------- CONSTRUCTORS ------------------------------ *
******************************************************************************/

Pass::Pass(Server &server) : ACommand(server)
{
    // Constructor
}

Pass::~Pass()
{
    // Destructor
}

/******************************************************************************
 * ------------------------------- MEMBER FUNCTIONS ------------------------- *
 *****************************************************************************/

void Pass::run(std::vector<std::string> args, int fdClient)
{
    if (args.size() != 2)
    {
        send(fdClient, "461 PASS :Not enough parameters\r\n", 34, 0);
        return;
    }
    if (this->_server.getUserByFd(fdClient)->getRegistered())
    {
        send(fdClient, "462 PASS :You may not reregister\r\n", 35, 0);
        return;
    }
    if (this->_server.getPassword() != args[1])
    {
        send(fdClient, "464 PASS :Password incorrect\r\n", 31, 0);
        return;
    }
    else
    {
        this->_server.getUserByFd(fdClient)->setRegistered(true);
    }
}