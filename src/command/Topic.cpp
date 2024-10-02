/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:17:17 by vpeinado          #+#    #+#             */
/*   Updated: 2024/10/02 17:52:11 by ffons-ti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

/*****************************************************************************
 * ------------------------------- CONSTRUCTORS ---------------------------- *
 ****************************************************************************/

Topic::Topic(Server &server) : ACommand(server)
{
    // Constructor
}

Topic::~Topic()
{
    // Destructor
}

/******************************************************************************
 * ------------------------------- MEMBER FUNCTIONS ------------------------- *
 *****************************************************************************/

int Topic::validArgs(std::vector<std::string> args, int fdClient)
{
    if (args.size() < 2)
    {
        send(fdClient, "461 TOPIC :Need More Params\r\n", 30, 0);
        return 0;
    }
    Channel *chan = this->_server.getChannelByName(args[1]);
    if (chan==NULL)
    {
        send(fdClient, "403 TOPIC :No Channel Found\r\n", 30, 0);
        return 0;
    }
    if (chan->GetClient(fdClient)==NULL)
    {
        send(fdClient, "442 TOPIC :Client Not On Channel\r\n", 35, 0);
        return 0;
    }
    if (args.size() == 3)
    {
        if(args[2][0] != ':')
        {
            send(fdClient, "461 TOPIC :Need More Params\r\n", 30, 0);
            return 0;
        }
    }
    return 1;
}

void Topic::run(std::vector<std::string> args, int fdClient)
{
    if (this->validArgs(args, fdClient) == 0)
        return;
    Channel *channel = this->_server.getChannelByName(args[1]);
    if (args.size() == 2)
    {
        std::string rply = args[1] + " TOPIC :" + channel->GetTopicName() + "\r\n";
        send(fdClient, rply.c_str(), rply.size(), 0);
    }
    else
    {
        if (channel->GetTopicRest() == 1 && channel->GetAdmin(fdClient) == NULL)
            send(fdClient, "461 TOPIC :Need more Privileges\r\n", 34, 0);
        else
            channel->SetTopicName(args[2]);
    }
}