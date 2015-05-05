#ifndef IB_CLIENT_WRAPPER_H
#define IB_CLIENT_WRAPPER_H
#include "IBClient.hpp"
#include <boost/python.hpp>
#include <boost/python/wrapper.hpp>
#include "Contract.h"
#include "Execution.h"
#include "ScannerSubscription.h"
#include "Order.h"

using namespace boost::python;

struct IBClientWrapper : public IBClient, wrapper<IBClient>
{
    void runStrategy(){
	if (override runStrategy = this->get_override("runStrategy")) {
	    runStrategy();
	    return;
	}
	IBClient::runStrategy(); 
    }
    void default_runStrategy() { this->IBClient::runStrategy(); }
    // events
    void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {
	if (override tickPrice = this->get_override("tickPrice")) 
	    tickPrice(tickerId, field, price, canAutoExecute);
	else
	    IBClient::tickPrice(tickerId, field, price, canAutoExecute);
    }
    void default_tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute) {
	this->IBClient::tickPrice(tickerId, field, price, canAutoExecute);
    }
    void tickSize(TickerId tickerId, TickType field, int size) {
	if (override tickSize = this->get_override("tickSize"))
	    tickSize(tickerId, field, size);
	else
	    IBClient::tickSize(tickerId, field, size);
    }
    void default_tickSize(TickerId tickerId, TickType field, int size) {
	this->IBClient::tickSize(tickerId, field, size);
    }
    void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
				double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice){
	if(override tickOptionComputation = this->get_override("tickOptionComputation"))
	    tickOptionComputation(tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
	else
	    IBClient::tickOptionComputation(tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
    }
    void default_tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
					double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice){
	this->IBClient::tickOptionComputation(tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
    }
    void tickGeneric(TickerId tickerId, TickType tickType, double value){
	if (override tickGeneric = this->get_override("tickGeneric"))
	    tickGeneric(tickerId, tickType, value);
	else
	    IBClient::tickGeneric(tickerId, tickType, value);
    }
    void default_tickGeneric(TickerId tickerId, TickType tickType, double value){
	this->IBClient::tickGeneric(tickerId, tickType, value);
    }
    void tickString(TickerId tickerId, TickType tickType, const IBString& value) {
	if (override tickString = this->get_override("tickString"))
	    tickString(tickerId, tickType, value);
	else
	    IBClient::tickString(tickerId, tickType, value);
    }
    void default_tickString(TickerId tickerId, TickType tickType, const IBString& value) {
	this->IBClient::tickString(tickerId, tickType, value);
    }
    void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
		 double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry){
	if (override tickEFP = this->get_override("tickEFP"))
	    tickEFP(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureExpiry, dividendImpact, dividendsToExpiry);
	else
	    IBClient::tickEFP(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureExpiry, dividendImpact, dividendsToExpiry);
    }
    void default_tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
		 double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry){
	this->IBClient::tickEFP(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureExpiry, dividendImpact, dividendsToExpiry);
    }
    void orderStatus(OrderId orderId, const IBString &status, int filled,
		     int remaining, double avgFillPrice, int permId, int parentId,
		     double lastFillPrice, int clientId, const IBString& whyHeld){
	if (override orderStatus = this->get_override("orderStatus"))
	    orderStatus(orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld);
	else
	    IBClient::orderStatus(orderId, status, filled, remaining, avgFillPrice, permId, parentId,
				  lastFillPrice, clientId, whyHeld);
    }
    void default_orderStatus(OrderId orderId, const IBString &status, int filled,
			     int remaining, double avgFillPrice, int permId, int parentId,
			     double lastFillPrice, int clientId, const IBString& whyHeld){
	this->IBClient::orderStatus(orderId, status, filled, remaining, avgFillPrice, permId, parentId,
				    lastFillPrice, clientId, whyHeld);
    }
    void openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState){
	if (override openOrder = this->get_override("openOrder"))
	    openOrder(orderId, contract, order, orderState);
	else
	    IBClient::openOrder(orderId, contract, order, orderState);
    }
    void default_openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState){
	this->IBClient::openOrder(orderId, contract, order, orderState);
    }
    void openOrderEnd(){
	if (override openOrderEnd = this->get_override("openOrderEnd"))
	    openOrderEnd();
	else
	    IBClient::openOrderEnd();
    }
    void default_openOrderEnd(){
	this->IBClient::openOrderEnd();
    }
    void winError(const IBString &str, int lastError){
	if (override winError = this->get_override("winError"))
	    winError(str, lastError);
	else
	    IBClient::winError(str, lastError);	
    }
    void default_winError(const IBString &str, int lastError){
	this->IBClient::winError(str, lastError);	
    }
    void connectionClosed(){
	if (override connectionClosed = this->get_override("connectionClosed"))
	    connectionClosed();
	else
	    IBClient::connectionClosed();
    }
    void default_connectionClosed(){
	this->IBClient::connectionClosed();
    }
    void updateAccountValue(const IBString& key, const IBString& val,
			    const IBString& currency, const IBString& accountName){
	if (override updateAccountValue = this->get_override("updateAccountValue")) 
	    updateAccountValue(key, val, currency, accountName);
	else
	    IBClient::updateAccountValue(key, val, currency, accountName);
    }
    void default_updateAccountValue(const IBString& key, const IBString& val,
			    const IBString& currency, const IBString& accountName){
	this->IBClient::updateAccountValue(key, val, currency, accountName);
    }
    void updatePortfolio(const Contract& contract, int position,
			 double marketPrice, double marketValue, double averageCost,
			 double unrealizedPNL, double realizedPNL, const IBString& accountName) {
	if (override updatePortfolio = this->get_override("updatePortfolio"))
	    updatePortfolio(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
	else
	    IBClient::updatePortfolio(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
    }
    void default_updatePortfolio(const Contract& contract, int position,
			 double marketPrice, double marketValue, double averageCost,
			 double unrealizedPNL, double realizedPNL, const IBString& accountName) {
	this->IBClient::updatePortfolio(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
    }
    void updateAccountTime(const IBString& timeStamp) {
	if (override updateAccountTime = this->get_override("updateAccountTime"))
	    updateAccountTime(timeStamp);
	else
	    IBClient::updateAccountTime(timeStamp);
    }
    void default_updateAccountTime(const IBString& timeStamp) {
	this->IBClient::updateAccountTime(timeStamp);
    }
    void accountDownloadEnd(const IBString& accountName) {
	if (override accountDownloadEnd = this->get_override("accountDownloadEnd"))
	    accountDownloadEnd(accountName);
	else
	    IBClient::accountDownloadEnd(accountName);
    }
    void default_accountDownloadEnd(const IBString& accountName) {
	this->IBClient::accountDownloadEnd(accountName);
    }
    void nextValidId(OrderId orderId) {
	if (override nextValidId = this->get_override("nextValidId"))
	    nextValidId(orderId);
	else
	    IBClient::nextValidId(orderId);
    }
    void default_nextValidId(OrderId orderId) {
	this->IBClient::nextValidId(orderId);
    }
    void contractDetails(int reqId, const ContractDetails& contractD) {
	if (override contractDetails = this->get_override("contractDetails"))
	    contractDetails(reqId, contractD);
	else
	    IBClient::contractDetails(reqId, contractD);
    }
    void default_contractDetails(int reqId, const ContractDetails& contractDetails) {
	this->IBClient::contractDetails(reqId, contractDetails);
    }
    void bondContractDetails(int reqId, const ContractDetails& contractDetails) {
	if (override bondContractDetails = this->get_override("bondContractDetails"))
	    bondContractDetails(reqId, contractDetails);
	else
	    IBClient::bondContractDetails(reqId, contractDetails);
    }
    void default_bondContractDetails(int reqId, const ContractDetails& contractDetails) {
	this->IBClient::bondContractDetails(reqId, contractDetails);
    }
    void contractDetailsEnd(int reqId) {
	if (override contractDetailsEnd = this->get_override("contractDetailsEnd")) 
	    contractDetailsEnd(reqId);
	else
	    IBClient::contractDetailsEnd(reqId);
    }
    void default_contractDetailsEnd(int reqId) {
	this->IBClient::contractDetailsEnd(reqId);
    }
    void execDetails(int reqId, const Contract& contract, const Execution& execution) {
	if (override execDetails = this->get_override("execDetails"))
	    execDetails(reqId, contract, execution);
	else
	    IBClient::execDetails(reqId, contract, execution);
    }
    void default_execDetails(int reqId, const Contract& contract, const Execution& execution) {
	this->IBClient::execDetails(reqId, contract, execution);
    }
    void execDetailsEnd(int reqId) {
	if (override execDetailsEnd = this->get_override("execDetailsEnd"))
	    execDetailsEnd(reqId);
	else
	    IBClient::execDetailsEnd(reqId);
    }
    void default_execDetailsEnd(int reqId) {
	if (override execDetailsEnd = this->get_override("execDetailsEnd"))
	    execDetailsEnd(reqId);
	else
	    IBClient::execDetailsEnd(reqId);
    }
    void error(const int id, const int errorCode, const IBString errorString) {
	if (override error = this->get_override("error"))
	    error(id, errorCode, errorString);
	IBClient::error(id, errorCode, errorString);
    }
    void default_error(const int id, const int errorCode, const IBString errorString) {
	this->IBClient::error(id, errorCode, errorString);	
    }
    void updateMktDepth(TickerId id, int position, int operation, int side, double price, int size) {
	if (override updateMktDepth = this->get_override("updateMktDepth"))
	    updateMktDepth(id, position, operation, side, price, size);
	else
	    IBClient::updateMktDepth(id, position, operation, side, price, size);
    }
    void default_updateMktDepth(TickerId id, int position, int operation, int side, double price, int size) {
	this->IBClient::updateMktDepth(id, position, operation, side, price, size);
    }
    void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation, int side, double price, int size) {
	if (override updateMktDepthL2 = this->get_override("updateMktDepthL2"))
	    updateMktDepthL2(id, position, marketMaker, operation, side, price, size);
	else
	    IBClient::updateMktDepthL2(id, position, marketMaker, operation, side, price, size);
    }
    void default_updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation, int side, double price, int size) {
	this->IBClient::updateMktDepthL2(id, position, marketMaker, operation, side, price, size);
    }
    void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {
	if (override updateNewsBulletin = this->get_override("updateNewsBulletin"))
	    updateNewsBulletin(msgId, msgType, newsMessage, originExch);
	else
	    IBClient::updateNewsBulletin(msgId, msgType, newsMessage, originExch);
    }
    void default_updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {
	this->IBClient::updateNewsBulletin(msgId, msgType, newsMessage, originExch);
    }
    void managedAccounts(const IBString& accountsList) {
	if (override managedAccounts = this->get_override("managedAccounts"))
	    managedAccounts(accountsList);
	else
	    IBClient::managedAccounts(accountsList);
    }
    void default_managedAccounts(const IBString& accountsList) {
	this->IBClient::managedAccounts(accountsList);
    }
    
    void receiveFA(faDataType pFaDataType, const IBString& cxml) {
	if (override receiveFA = this->get_override("receiveFA"))
	    receiveFA(pFaDataType, cxml);
	else
	    IBClient::receiveFA(pFaDataType, cxml);
    }
    void default_receiveFA(faDataType pFaDataType, const IBString& cxml) {
	this->IBClient::receiveFA(pFaDataType, cxml);
    }
    
    void historicalData(TickerId reqId, const IBString& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps) {
	if (override historicalData = this->get_override("historicalData"))
	    historicalData(reqId, date, open, high, low, close, volume, barCount, WAP, hasGaps);
	else
	    IBClient::historicalData(reqId, date, open, high, low, close, volume, barCount, WAP, hasGaps);
    }
    void default_historicalData(TickerId reqId, const IBString& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps) {
	this->IBClient::historicalData(reqId, date, open, high, low, close, volume, barCount, WAP, hasGaps);
    }
    
    void scannerParameters(const IBString &xml) {
	if (override scannerParameters = this->get_override("scannerParameters"))
	    scannerParameters(xml);
	else
	    IBClient::scannerParameters(xml);
    }
    void default_scannerParameters(const IBString &xml) {
	this->IBClient::scannerParameters(xml);
    }
    
    void scannerData(int reqId, int rank, const ContractDetails &contractDetails, const IBString &distance, const IBString &benchmark, const IBString &projection, const IBString &legsStr) {
	if (override scannerData = this->get_override("scannerData"))
	    scannerData(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
	else
	    IBClient::scannerData(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
    }
    void default_scannerData(int reqId, int rank, const ContractDetails &contractDetails, const IBString &distance, const IBString &benchmark, const IBString &projection, const IBString &legsStr) {
	this->IBClient::scannerData(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
    }
    
    void scannerDataEnd(int reqId) {
	if (override scannerDataEnd = this->get_override("scannerDataEnd"))
	    scannerDataEnd(reqId);
	else
	    IBClient::scannerDataEnd(reqId);
    }
    void default_scannerDataEnd(int reqId) {
	this->IBClient::scannerDataEnd(reqId);
    }
    
    void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count) {
	if (override realtimeBar = this->get_override("realtimeBar"))
	    realtimeBar(reqId, time, open, high, low, close, volume, wap, count);
	else
	    IBClient::realtimeBar(reqId, time, open, high, low, close, volume, wap, count);
    }
    void default_realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count) {
	this->IBClient::realtimeBar(reqId, time, open, high, low, close, volume, wap, count);
    }
    
    void currentTime(long time) {
	if (override currentTime = this->get_override("currentTime"))
	    currentTime(time);
	else
	    IBClient::currentTime(time);
    }
    void default_currentTime(long time) {
	this->IBClient::currentTime(time);
    }
    
    void fundamentalData(TickerId reqId, const IBString& data) {
	if (override fundamentalData = this->get_override("fundamentalData"))
	    fundamentalData(reqId, data);
	else
	    IBClient::fundamentalData(reqId, data);
    }
    void default_fundamentalData(TickerId reqId, const IBString& data) {
	this->IBClient::fundamentalData(reqId, data);
    }
    
    void deltaNeutralValidation(int reqId, const UnderComp& underComp) {
	if (override deltaNeutralValidation = this->get_override("deltaNeutralValidation"))
	    deltaNeutralValidation(reqId, underComp);
	else
	    IBClient::deltaNeutralValidation(reqId, underComp);
    }
    void default_deltaNeutralValidation(int reqId, const UnderComp& underComp) {
	this->IBClient::deltaNeutralValidation(reqId, underComp);
    }
    
    void tickSnapshotEnd(int reqId) {
	if (override tickSnapshotEnd = this->get_override("tickSnapshotEnd"))
	    tickSnapshotEnd(reqId);
	else
	    IBClient::tickSnapshotEnd(reqId);
    }
    void default_tickSnapshotEnd(int reqId) {
	this->IBClient::tickSnapshotEnd(reqId);
    }
    
    void marketDataType(TickerId reqId, int marketD) {
	if (override marketDataType = this->get_override("marketDataType"))
	    marketDataType(reqId, marketD);
	else
	    IBClient::marketDataType(reqId, marketD);
    }
    void default_marketDataType(TickerId reqId, int marketDataType) {
	this->IBClient::marketDataType(reqId, marketDataType);
    }
    
    void commissionReport( const CommissionReport& commissionR) {
	if (override commissionReport = this->get_override("commissionReport"))
	    commissionReport(commissionR);
	else
	    IBClient::commissionReport(commissionR);
    }
    void default_commissionReport( const CommissionReport& commissionReport) {
	this->IBClient::commissionReport(commissionReport);
    }
    
    void position( const IBString& account, const Contract& contract, int pos, double avgCost) {
	if (override position = this->get_override("position"))
	    position(account, contract, pos, avgCost);
	else
	    IBClient::position(account, contract, pos, avgCost);
    }
    void default_position( const IBString& account, const Contract& contract, int position, double avgCost) {
	this->IBClient::position(account, contract, position, avgCost);
    }
    
    void positionEnd() {
	if (override positionEnd = this->get_override("positionEnd"))
	    positionEnd();
	else
	    IBClient::positionEnd();
    }
    void default_positionEnd() {
	this->IBClient::positionEnd();
    }
    
    void accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {
	if (override accountSummary = this->get_override("accountSummary"))
	    accountSummary(reqId, account, tag, value, curency);
	else
	    IBClient::accountSummary(reqId, account, tag, value, curency);
    }
    void default_accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {
	this->IBClient::accountSummary(reqId, account, tag, value, curency);
    }
    
    void accountSummaryEnd( int reqId) {
	if (override accountSummaryEnd = this->get_override("accountSummaryEnd"))
	    accountSummaryEnd(reqId);
	else
	    IBClient::accountSummaryEnd(reqId);
    }
    void default_accountSummaryEnd( int reqId) {
	this->IBClient::accountSummaryEnd(reqId);
    }
};


#endif
