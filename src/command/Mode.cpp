/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffons-ti <ffons-ti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:44:44 by ffons-ti          #+#    #+#             */
/*   Updated: 2024/10/06 18:20:29 by ffons-ti         ###   ########.fr       */
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
	if (args.size() < 2)
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
	if (args.size() == 3 && chan->GetAdmin(fdClient) == NULL)
	{
		send(fdClient, "482 MODE :Need more Privileges\r\n", 33, 0);
		return 0;
	}
	return 1;
}

void changeInvite(Channel *channel, char oper)
{
	if (oper == '+')
		channel->SetInvitOnly(1);
	else if (oper == '-')
		channel->SetInvitOnly(0);
}
void changeTopic(Channel *channel, char oper)
{
	if (oper == '+')
		channel->SetTopicRestriction(1);
	else if (oper == '-')
		channel->SetTopicRestriction(0);
}

void changeKey(Channel *channel, char oper, std::vector<std::string> args, int *offset)
{
	
	if (oper == '+')
	{
        if (args.size() < *offset + 4)
	    {
		    send(fdClient, "461 MODE :Need More Params\r\n", 29, 0);
		    return ;
	    }
		channel->SetHasKey(1);
		channel->SetKey(args[3 + *offset]);
		(*offset)++;
	}
	else if (oper == '-')
	{
		channel->SetHasKey(0);
		channel->SetKey("");
	}
}
void changeOper(Channel *channel, char oper, std::vector<std::string> args, int *offset)
{
	if (args.size() < *offset + 4)
	{
		send(fdClient, "461 MODE :Need More Params\r\n", 29, 0);
		return ;
	}
    Client *cli = channel->GetClientByName(args[3 + offset]);
    (*offset)++;
    if (cli == NULL)
    {
        send(fdClient, "441 MODE :They aren't on that channel\r\n", 40, 0);
		return ;
    }
	if (oper == '+')
	{
        if (channel->GetAdmin(cli->GetClientFd()) != NULL)
        {
            send(fdClient, "400 MODE :Already an operator\r\n", 32, 0);
		    return ;
        }
		else
        channel->changeClientToAdmin(cli->getNickname);
	}
	else if (oper == '-')
	{
        if (channel->GetAdmin(cli->GetClientFd()) == NULL)
        {
            send(fdClient, "400 MODE :Not an operator\r\n", 32, 0);
		    return ;
        }
		else
        channel->changeAdminToClient(cli->getNickname);
	}
}

void Mode::run(std::vector<std::string> args, int fdClient)
{
	char oper = '\0';

	if (validArgs(args, fdClient) == 0)
		return ;
	
	Channel *channel = this->_server.getChannelByName(args[1]);
	if (args.size() == 2)
	{
		std::string modes;
		std::string rply = "324 " + channel->GetChannelName();
		if (channel->GetTopicRest())
			modes += "t";
		if (channel->GetInviteOnly())
			modes += "i";
		if (channel->GetHasKey())
			modes += "k";
		if (channel->GetLimit() > 0)
			modes += "l";
		if (modes.size())
			rply += " +" + modes;
		send(fdClient, rply.c_str(), rply.size(), 0);
	}
	else
	{
		int offset = 0;
		std::string modeset = args[2];
		for(size_t i = 0; i < modeset.size(); i++)
		{
			if (modeset[i] == '+' || modeset[i] == '-')
				oper = modeset[i];
			else
			{
				if(modeset[i] == 'i')
					changeInvite(channel, oper);
				else if (modeset[i] == 't')
					changeTopic(channel, oper);
				else if (modeset[i] == 'k')
					changeKey(channel, oper, args, &offset);
				else if (modeset[i] == 'o')
					changeOper(channel, oper, args, &offset);
				else if (modeset[i] == 'l')
					;
				else
					send(fdClient, "472 MODE :is unknown mode char to me\r\n", 39, 0);
			}
		}
	}
}