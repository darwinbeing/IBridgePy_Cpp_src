#ifndef IB_CLIENT_HPP
#define IB_CLIENT_HPP
#include "Contract.h"
#include "EWrapper.h"
#include <memory>
#include "EPosixClientSocket.h"
#include <fstream>


class IBClient : public EWrapper
{
public:

    IBClient();
    ~IBClient();
    
    void processMessages();
    
    virtual void runStrategy(){};
public:
    // Custimzed Interface
    void setTimeOut(time_t t);
public:
    // Connection and Server
    bool connect(const char * host, unsigned int port, int clientId = 0);
    void disconnect();
    bool isConnected() const;
    void reqGlobalCancel(){m_pClient->reqGlobalCancel();}
    int serverVersion(){return m_pClient->serverVersion();}
    IBString TwsConnectionTime(){return m_pClient->TwsConnectionTime();}
    bool checkMessages(){return m_pClient->checkMessages();}
    void setServerLogLevel(int level){m_pClient->setServerLogLevel(level);}
    void reqCurrentTime(){m_pClient->reqCurrentTime();}

    //Other helpers
    //::Market Data
    void reqMktData(TickerId id, const Contract &contract,
		    const IBString &genericTicks, bool snapshot) {m_pClient->reqMktData(id, contract, genericTicks, snapshot);}
    void cancelMktData(TickerId id) {m_pClient->cancelMktData(id);}
    void calculateImpliedVolatility(TickerId reqId, const Contract &contract, double optionPrice, double underPrice) 
	{m_pClient->calculateImpliedVolatility(reqId, contract, optionPrice, underPrice);}
    void cancelCalculateImpliedVolatility(TickerId reqId) {m_pClient->cancelCalculateImpliedVolatility(reqId);}
    void calculateOptionPrice(TickerId reqId, const Contract &contract, double volatility, double underPrice) {m_pClient->calculateOptionPrice(reqId, contract, volatility, underPrice);}
    void cancelCalculateOptionPrice(TickerId reqId){m_pClient->cancelCalculateOptionPrice(reqId);}
    void reqMarketDataType(int marketDataType) {m_pClient->reqMarketDataType(marketDataType);}
    // Order
    void placeOrder(OrderId id, const Contract &contract, const Order &order) {m_pClient->placeOrder(id, contract, order);}
    void cancelOrder(OrderId id) {m_pClient->cancelOrder(id);}
    void reqOpenOrders() {m_pClient->reqOpenOrders();}
    void reqAutoOpenOrders(bool bAutoBind){m_pClient->reqAutoOpenOrders(bAutoBind);}
    void reqAllOpenOrders(){m_pClient->reqAllOpenOrders();}
    void reqIds(int numIds){m_pClient->reqIds(numIds);}
    //void reqIds(int numIds){m_pClient->reqIDs(numIds);}
    void exerciseOptions(TickerId tickerId, const Contract &contract, int exerciseAction, int exerciseQuantity,
			 const IBString &account, int override) {m_pClient->exerciseOptions(tickerId, contract, exerciseAction, exerciseQuantity, account, override);}
    // Account
    void reqAccountUpdates(bool subscribe, const IBString& acctCode){m_pClient->reqAccountUpdates(subscribe, acctCode);}
    // Excutions
    void reqExecutions(int reqId, const ExecutionFilter& filter){m_pClient->reqExecutions(reqId, filter);}
    // Contract Details
    void reqContractDetails(int reqId, const Contract &contract){m_pClient->reqContractDetails(reqId, contract);}
    // Market Depth
    void reqMktDepth(TickerId tickerId, const Contract &contract, int numRows){m_pClient->reqMktDepth(tickerId, contract, numRows);}
    void cancelMktDepth(TickerId tickerId){m_pClient->cancelMktDepth(tickerId);}
    // News Bulletins
    void reqNewsBulletins(bool allMsgs){m_pClient->reqNewsBulletins(allMsgs);}
    void cancelNewsBulletins(){m_pClient->cancelNewsBulletins();}
    // Finacial Advisors
    void reqManagedAccts(){m_pClient->reqManagedAccts();}
    void requestFA(faDataType pFaDataType){m_pClient->requestFA(pFaDataType);}
    void replaceFA(faDataType pFaDataType, const IBString& cxml){m_pClient->replaceFA(pFaDataType, cxml);}
    void reqAccountSummary( int reqId, const IBString& groupName, const IBString& tags){m_pClient->reqAccountSummary(reqId, groupName, tags);}
    void cancelAccountSummary( int reqId){m_pClient->cancelAccountSummary(reqId);}
    void reqPositions(){m_pClient->reqPositions();}
    void cancelPositions(){m_pClient->cancelPositions();}
    // Historical Data
    void reqHistoricalData( TickerId id, const Contract &contract, const IBString &endDateTime, const IBString &durationStr,
			    const IBString & barSizeSetting, const IBString &whatToShow, int useRTH, int formatDate)
	{m_pClient->reqHistoricalData(id, contract, endDateTime, durationStr, barSizeSetting, whatToShow, useRTH, formatDate);}
    void cancelHistoricalData(TickerId tickerId ){m_pClient->cancelHistoricalData(tickerId);}
    // Market Scanner
    void reqScannerParameters(){m_pClient->reqScannerParameters();}
    void reqScannerSubscription(int tickerId, const ScannerSubscription &subscription){m_pClient->reqScannerSubscription(tickerId, subscription);}
    void cancelScannerSubscription(int tickerId){m_pClient->cancelScannerSubscription(tickerId);}
    // Real Time Bars
    void reqRealTimeBars(TickerId id, const Contract &contract, int barSize, const IBString &whatToShow, bool useRTH){m_pClient->reqRealTimeBars(id, contract, barSize, whatToShow, useRTH);}
    void cancelRealTimeBars(TickerId tickerId ){m_pClient->cancelRealTimeBars(tickerId);}
    // Fundamental Data
    void reqFundamentalData(TickerId reqId, const Contract& contract, const IBString& reportType){m_pClient->reqFundamentalData(reqId, contract, reportType);}
    void cancelFundamentalData(TickerId reqId){m_pClient->cancelFundamentalData(reqId);}

    
public:

    // events
    virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute);
    virtual void tickSize(TickerId tickerId, TickType field, int size);
    virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
					double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
    virtual void tickGeneric(TickerId tickerId, TickType tickType, double value);
    virtual void tickString(TickerId tickerId, TickType tickType, const IBString& value);
    virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
			 double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry);
    virtual void orderStatus(OrderId orderId, const IBString &status, int filled,
			     int remaining, double avgFillPrice, int permId, int parentId,
			     double lastFillPrice, int clientId, const IBString& whyHeld);
    virtual void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&);
    virtual void openOrderEnd();
    virtual void winError(const IBString &str, int lastError);
    virtual void connectionClosed();
    virtual void updateAccountValue(const IBString& key, const IBString& val,
				    const IBString& currency, const IBString& accountName);
    virtual void updatePortfolio(const Contract& contract, int position,
				 double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const IBString& accountName);
    virtual void updateAccountTime(const IBString& timeStamp);
    virtual void accountDownloadEnd(const IBString& accountName);
    virtual void nextValidId(OrderId orderId);
    virtual void contractDetails(int reqId, const ContractDetails& contractDetails);
    virtual void bondContractDetails(int reqId, const ContractDetails& contractDetails);
    virtual void contractDetailsEnd(int reqId);
    virtual void execDetails(int reqId, const Contract& contract, const Execution& execution);
    virtual void execDetailsEnd(int reqId);
    virtual void error(const int id, const int errorCode, const IBString errorString);
    virtual void updateMktDepth(TickerId id, int position, int operation, int side,
				double price, int size);
    virtual void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
				  int side, double price, int size);
    virtual void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch);
    virtual void managedAccounts(const IBString& accountsList);
    virtual void receiveFA(faDataType pFaDataType, const IBString& cxml);
    virtual void historicalData(TickerId reqId, const IBString& date, double open, double high,
				double low, double close, int volume, int barCount, double WAP, int hasGaps);
    virtual void scannerParameters(const IBString &xml);
    virtual void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
			     const IBString &distance, const IBString &benchmark, const IBString &projection,
			     const IBString &legsStr);
    virtual void scannerDataEnd(int reqId);
    virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
			     long volume, double wap, int count);
    virtual void currentTime(long time);
    virtual void fundamentalData(TickerId reqId, const IBString& data);
    virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp);
    virtual void tickSnapshotEnd(int reqId);
    virtual void marketDataType(TickerId reqId, int marketDataType);
    virtual void commissionReport( const CommissionReport& commissionReport);
    virtual void position( const IBString& account, const Contract& contract, int position, double avgCost);
    virtual void positionEnd();
    virtual void accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency);
    virtual void accountSummaryEnd( int reqId);

public:

    enum MSGLEVEL {SYSERR, IBERROR, IBWARNING, IBINFO, IBDEBUG, IBEVENT};
    long addMessageLevel(MSGLEVEL level){messageLevel |= 1L << level; return messageLevel;}
    long rmMessageLevel (MSGLEVEL level){messageLevel &= (~1L) << level; return messageLevel;}
    bool isMessageOn(MSGLEVEL level){return messageLevel & (1L << level);};
    long getMessageLevel(){return messageLevel;};
    void message(MSGLEVEL level, const std::string&  m);
    void logOn();
    void logOff();
public:
    bool echo;
    std::string logFileName;
    std::string logPath;
    time_t timeOut;  // in sec 

protected:

    std::shared_ptr<EPosixClientSocket> m_pClient;
    long messageLevel;
    std::ofstream logFile;
    std::string getTimeStamp();

};


#endif
