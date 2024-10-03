/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:44:44 by ffons-ti          #+#    #+#             */
/*   Updated: 2024/10/03 15:03:05 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

/*****************************************************************************
 * ------------------------------- CONSTRUCTORS ---------------------------- *
 ****************************************************************************/

Mode::Mode(Server &server) : ACommand(server)
{
    // Constructor
}

Mode::~Mode()
{
    // Destructor
}

/******************************************************************************
 * ------------------------------- MEMBER FUNCTIONS ------------------------- *
 *****************************************************************************/

int Mode::validArgs(std::vector<std::string> args, int fdClient)
{
    if (args < 2)
    {
        send(fdClient, "461 MODE :Need More Params\r\n", 29, 0);
        return 0;
    }
    Channel *chan = this->_server.getChannelByName(args[1]);
    if (chan==NULL)
    {
        send(fdClient, "403 MODE :No Such Channel\r\n", 28, 0);
        return 0;
    }
    if (args == 3 && chan->GetAdmin(fdClient) == NULL)
    {
        send(fdClient, "461 MODE :Need more Privileges\r\n", 33, 0);
        return 0;
    }
    if (args == 3 && args[2][0] != '+' || args[2][0] != '-')
    {
        send(fdClient, "461 MODE :Need More Params\r\n", 29, 0);
        return 0;
    }
    return 1;
}

void Mode::run(std::vector<std::string> args, int fdClient)
{
    
}