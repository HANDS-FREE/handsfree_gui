/***********************************************************************************************************************
* Copyright (c) Hands Free Team. All rights reserved.
* FileName: hf_link.cpp
* Contact:  QQ Exchange Group -- 521037187
* Version:  V2.0
*
* LICENSING TERMS:
* The Hands Free is licensed generally under a permissive 3-clause BSD license.
* Contributions are requiredto be made under the same license.
*
* History:
* <author>      <time>      <version>      <desc>
* luke liao       2016.4.1   V1.0           creat this file
*
* Description: define the handfree pc software interface
***********************************************************************************************************************/

#ifndef HF_HW_H_
#define HF_HW_H_

#include <fstream>
#include <handsfree_hw/transport_serial.h>
#include <hf_link/hf_link.h>
#include <cstdlib>
#include <QObject>
//#define DEBUG
namespace handsfree_hw {

class HF_HW:public QObject{
	Q_OBJECT

public:
    HF_HW(std::string url, std::string config_addr);

    bool updateCommand(const Command &command, int count);

    void updateRobot();

    inline RobotAbstract* getRobotAbstract()
    {
        return &my_robot_;
    }


    inline boost::shared_ptr<boost::asio::io_service> getIOinstace()
    {
        return port_->getIOinstace();
    }

    void setParam(const TransportParam &param){
        this->port_->setParam(param);
    }

    bool reconfig()
    {

    }

    inline bool initialize_ok () const
    {
        return initialize_ok_;
    }

    inline void checkHandshake()
    {
        if (hflink_->getReceiveRenewFlag(SHAKING_HANDS)==1)
        {
            sendCommand(SHAKING_HANDS);
						#ifdef DEBUG
            std::cout<<"send shake hands"<<std::endl;
						#endif
				}
    }
    inline void sendCommand(const Command command_state)
    {
			if(!this->enable_)return ;
			#ifdef DEBUG
        std::cout<<"send message"<<command_state <<std::endl;
			#endif
				hflink_->masterSendCommand(command_state);
        Buffer data(hflink_->getSerializedData(), hflink_->getSerializedLength() + hflink_->getSerializedData());
        port_->writeBuffer(data);
    }
signals:
    void newMsg() ;
    void transportStop() ;
    void transportStart() ;
public slots:
    void stopTransport(){
        emit this->transportStop();
				this->enable_ = false ;
    }

    void startTransport(){
        emit this->transportStart();
				this->enable_ = true ;
		}
private:
    boost::shared_ptr<Transport> port_;
    boost::shared_ptr<HFLink> hflink_;
    boost::shared_ptr<boost::asio::deadline_timer> timer_;

    //for reading config file
    std::fstream file_;
    bool initialize_ok_;
    //for updating data
    int hflink_command_set_[LAST_COMMAND_FLAG];
    int hflink_freq_[LAST_COMMAND_FLAG];
    int hflink_count_[LAST_COMMAND_FLAG];
    int hflink_command_set_current_[LAST_COMMAND_FLAG];

		bool enable_ ;
    int time_out_;
    bool time_out_flag_;
    boost::mutex wait_mutex_;
    bool ack_ready_;
    void timeoutHandler(const boost::system::error_code &ec);

    inline uint8_t checkUpdate(const Command command_state)
    {
        if (hflink_command_set_current_[command_state] & hflink_->getReceiveRenewFlag(command_state))
        {
            return 1;
        }
        if (hflink_command_set_current_[command_state] == 0 ) return 1;
        return 0;
    }


    // a single object for robot
    RobotAbstract my_robot_;
};

}


#endif /* HF_HW_H_ */
