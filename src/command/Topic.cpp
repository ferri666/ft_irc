/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:17:17 by vpeinado          #+#    #+#             */
/*   Updated: 2024/10/09 14:40:22 by ffons-ti         ###   ########.fr       */
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
        this->_server.sendError(461, this->_server.getUserByFd(fdClient)->getNickname(), channelName, fdClient, " :Not enough parameters\r\n");
        return 0;
    }
    Channel *chan = this->_server.getChannelByName(args[1]);
    if (chan==NULL)
    {
        this->_server.sendError(403, this->_server.getUserByFd(fdClient)->getNickname(), channelName, fdClient, " :No such channel\r\n");
        return 0;
    }
    if (chan->GetClient(fdClient)==NULL)
    {
        this->_server.sendError(442, this->_server.getUserByFd(fdClient)->getNickname(), channelName, fdClient, " :You're not on that channel\r\n");
        return 0;
    }
    if (args.size() == 3)
    {
        if(args[2][0] != ':')
        {
            this->_server.sendError(461, this->_server.getUserByFd(fdClient)->getNickname(), channelName, fdClient, " :Not enough parameters\r\n");
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
        std::string rply;
        if (channel->GetTopicName() != NULL)
            rply = this->_server.getUserByFd(fdClient)->getNickname() + " " + channel->GetChannelName() + " :" + channel->GetTopicName();
        else
            rply = this->_server.getUserByFd(fdClient)->getNickname() + " " + channel->GetChannelName() + " :No topic is set";
        this->_server.sendResponse(rply, fdClient);
    }
    else
    {
        if (channel->GetTopicRest() == 1 && channel->GetAdmin(fdClient) == NULL)
            this->_server.sendError(482, this->_server.getUserByFd(fdClient)->getNickname(), channelName, fdClient, " :You're not channel operator\r\n");
        else
            channel->SetTopicName(args[2]);
    }
}