#include "IBClient.hpp"
#include "EPosixClientSocketPlatform.h"
#include "EPosixClientSocket.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <boost/algorithm/string.hpp>

IBClient::IBClient()
    : m_pClient(new EPosixClientSocket(this))
{
    timeOut = 0;
    echo = false;
    logFileName = "tmp.log";
    logPath = "./";
}

IBClient::~IBClient()
{
    logFile.close();
}

bool IBClient::connect(const char *host, unsigned int port, int clientId)
{
    // trying to connect
    std::string address = !( host && *host) ? "127.0.0.1" : host;
    std::stringstream ss;
    ss << "Connecting to " << address << ":" << port << "with client ID " << clientId;
    message(IBINFO, ss.str());
    
    bool bRes = m_pClient->eConnect( host, port, clientId);
    ss.str(""); 
	
    if (bRes) 
	ss << "Connected to " << address << ":" << port << " with client ID " << clientId;
    else
	ss << "Cannot connect to " << address << ":" << port << " with client ID " << clientId;
    message(IBINFO, ss.str());

    return bRes;
}

void IBClient::disconnect()
{
    m_pClient->eDisconnect();
    message(IBINFO, "Disconected");
}

bool IBClient::isConnected() const
{
    return m_pClient->isConnected();
}

void IBClient::setTimeOut(time_t t){timeOut = t;}

void IBClient::processMessages()
{
    fd_set readSet, writeSet, errorSet;
    
    struct timeval tval;
    tval.tv_sec = timeOut;
    tval.tv_usec = 0;
    
    runStrategy();

    
    if( m_pClient->fd() >= 0 ) {
	
	FD_ZERO( &readSet);
	errorSet = writeSet = readSet;

	FD_SET( m_pClient->fd(), &readSet);
	
	if( !m_pClient->isOutBufferEmpty())
	    FD_SET( m_pClient->fd(), &writeSet);

	FD_CLR( m_pClient->fd(), &errorSet);
	
	int ret = select( m_pClient->fd() + 1, &readSet, &writeSet, &errorSet, &tval);
	
	if( ret == 0) { // timeout
			return;
	}

	if( ret < 0) {	// error
	    disconnect();
	    return;
	}
	
	if( m_pClient->fd() < 0)
	    return;
	
	if( FD_ISSET( m_pClient->fd(), &errorSet)) {
	    // error on socket
	    m_pClient->onError();
	}
	
	if( m_pClient->fd() < 0)
	    return;
	
	if( FD_ISSET( m_pClient->fd(), &writeSet)) {
	    // socket is ready for writing
	    m_pClient->onSend();
	}
	
	if( m_pClient->fd() < 0)
	    return;
	
	if( FD_ISSET( m_pClient->fd(), &readSet)) {
	    // socket is ready for reading
	    m_pClient->onReceive();
	}
    }
}

///////////////////////////////////////////////////////////////////
// events
void IBClient::orderStatus( OrderId orderId, const IBString &status, int filled,
	   int remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const IBString& whyHeld) {}

void IBClient::nextValidId( OrderId orderId) {}

void IBClient::currentTime( long time) {}

void IBClient::error(const int id, const int errorCode, const IBString errorString) {}

void IBClient::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {}
void IBClient::tickSize( TickerId tickerId, TickType field, int size) {}
void IBClient::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
				      double optPrice, double pvDividend,
				      double gamma, double vega, double theta, double undPrice) {}
void IBClient::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void IBClient::tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
void IBClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
		       double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
void IBClient::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState& ostate) {}
void IBClient::openOrderEnd() {}
void IBClient::winError( const IBString &str, int lastError) {}
void IBClient::connectionClosed() {}
void IBClient::updateAccountValue(const IBString& key, const IBString& val,
				  const IBString& currency, const IBString& accountName) {}
void IBClient::updatePortfolio(const Contract& contract, int position,
			       double marketPrice, double marketValue, double averageCost,
			       double unrealizedPNL, double realizedPNL, const IBString& accountName){}
void IBClient::updateAccountTime(const IBString& timeStamp) {}
void IBClient::accountDownloadEnd(const IBString& accountName) {}
void IBClient::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void IBClient::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void IBClient::contractDetailsEnd( int reqId) {}
void IBClient::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void IBClient::execDetailsEnd( int reqId) {}

void IBClient::updateMktDepth(TickerId id, int position, int operation, int side,
			      double price, int size) {}
void IBClient::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
				int side, double price, int size) {}
void IBClient::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
void IBClient::managedAccounts( const IBString& accountsList) {}
void IBClient::receiveFA(faDataType pFaDataType, const IBString& cxml) {}
void IBClient::historicalData(TickerId reqId, const IBString& date, double open, double high,
			      double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
void IBClient::scannerParameters(const IBString &xml) {}
void IBClient::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
			   const IBString &distance, const IBString &benchmark, const IBString &projection,
			   const IBString &legsStr) {}
void IBClient::scannerDataEnd(int reqId) {}
void IBClient::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
			   long volume, double wap, int count) {}
void IBClient::fundamentalData(TickerId reqId, const IBString& data) {}
void IBClient::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void IBClient::tickSnapshotEnd(int reqId) {}
void IBClient::marketDataType(TickerId reqId, int marketDataType) {}
void IBClient::commissionReport( const CommissionReport& commissionReport) {}
void IBClient::position( const IBString& account, const Contract& contract, int position, double avgCost) {}
void IBClient::positionEnd() {}
void IBClient::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {}
void IBClient::accountSummaryEnd( int reqId) {}

//Message Level
void IBClient::message(MSGLEVEL level, const std::string&  m)
{
    std::stringstream ss;
    ss.str("");
    if (isMessageOn(level)) {
	ss << "[" << getTimeStamp()<< "] ";
	switch (level) {
	case SYSERR :
	    ss << "SYSERR: "; break;
	case IBERROR :
	    ss << "IBERROR: "; break;
	case IBWARNING:
	    ss << "IBWARNING: "; break;
	case IBEVENT:
	    ss << "IBEVENT: "; break;
	case IBINFO:
	    ss << "IBINFO: "; break;
	case IBDEBUG:
	    ss << "IBDEBUG: "; break;
	default :
	    ss << "UNKNOWN: "; break;
	}
	ss << m << std::endl;
	if (echo) std::cout << ss.str() << std::endl;
	if (logFile.is_open()) logFile << ss.str() << std::endl;
    }
}

void IBClient::logOn()
{
    logFile.open((logPath+logFileName).c_str(), std::ofstream::out);
}

void IBClient::logOff()
{
    if (logFile.is_open()) logFile.close();
}

std::string IBClient::getTimeStamp()
{
    time_t ltime;
    ltime = time(NULL);
    std::string timestring(asctime(localtime(&ltime)));
    boost::algorithm::trim(timestring);
    return timestring;
}
