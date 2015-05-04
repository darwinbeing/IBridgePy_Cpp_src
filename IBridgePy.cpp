#include <boost/python.hpp>
using namespace boost::python;
#include <string>
#include "Contract.h"
#include "OrderState.h"
#include "Execution.h"
#include "ScannerSubscription.h"
#include "IBClientWrapper.hpp"
#include "CommissionReport.h"

BOOST_PYTHON_MODULE(IBCpp)
{
	
    class_<Execution>("Execution")
	.def_readwrite("execId",&Execution::execId)
	.def_readwrite("time",&Execution::time)
	.def_readwrite("acctNumber",&Execution::acctNumber)
	.def_readwrite("exchange",&Execution::exchange)
	.def_readwrite("side",&Execution::side)
	.def_readwrite("shares",&Execution::shares)
	.def_readwrite("price",&Execution::price)
	.def_readwrite("permId",&Execution::permId)
	.def_readwrite("clientId",&Execution::clientId)
	.def_readwrite("orderId",&Execution::orderId)
	.def_readwrite("liquidation",&Execution::liquidation)
	.def_readwrite("cumQty",&Execution::cumQty)
	.def_readwrite("avgPrice",&Execution::avgPrice)
	.def_readwrite("orderRef",&Execution::orderRef)
	.def_readwrite("evRule",&Execution::evRule)
	.def_readwrite("evMultiplier",&Execution::evMultiplier)
	;

    class_<ExecutionFilter>("ExecutionFilter")
	.def_readwrite("m_clientId",&ExecutionFilter::m_clientId)
	.def_readwrite("m_acctCode",&ExecutionFilter::m_acctCode)
	.def_readwrite("m_time",&ExecutionFilter::m_time)
	.def_readwrite("m_symbol",&ExecutionFilter::m_symbol)
	.def_readwrite("m_secType",&ExecutionFilter::m_secType)
	.def_readwrite("m_exchange",&ExecutionFilter::m_exchange)
	.def_readwrite("m_side",&ExecutionFilter::m_side)
	;

    class_<ScannerSubscription>("ScannerSubscription")
	.def_readwrite("numberOfRows",&ScannerSubscription::numberOfRows)
	.def_readwrite("instrument",&ScannerSubscription::instrument)
	.def_readwrite("locationCode",&ScannerSubscription::locationCode)
	.def_readwrite("scanCode",&ScannerSubscription::scanCode)
	.def_readwrite("abovePrice",&ScannerSubscription::abovePrice)
	.def_readwrite("belowPrice",&ScannerSubscription::belowPrice)
	.def_readwrite("aboveVolume",&ScannerSubscription::aboveVolume)
	.def_readwrite("marketCapAbove",&ScannerSubscription::marketCapAbove)
	.def_readwrite("marketCapBelow",&ScannerSubscription::marketCapBelow)
	.def_readwrite("moodyRatingAbove",&ScannerSubscription::moodyRatingAbove)
	.def_readwrite("moodyRatingBelow",&ScannerSubscription::moodyRatingBelow)
	.def_readwrite("spRatingAbove",&ScannerSubscription::spRatingAbove)
	.def_readwrite("spRatingBelow",&ScannerSubscription::spRatingBelow)
	.def_readwrite("maturityDateAbove",&ScannerSubscription::maturityDateAbove)
	.def_readwrite("maturityDateBelow",&ScannerSubscription::maturityDateBelow)
	.def_readwrite("couponRateAbove",&ScannerSubscription::couponRateAbove)
	.def_readwrite("couponRateBelow",&ScannerSubscription::couponRateBelow)
	.def_readwrite("excludeConvertible",&ScannerSubscription::excludeConvertible)
	.def_readwrite("averageOptionVolumeAbove",&ScannerSubscription::averageOptionVolumeAbove)
	.def_readwrite("scannerSettingPairs",&ScannerSubscription::scannerSettingPairs)
	.def_readwrite("stockTypeFilter",&ScannerSubscription::stockTypeFilter)
	;

    class_<OrderState>("OrderState")
	.def_readwrite("status",&OrderState::status)
	.def_readwrite("initMargin",&OrderState::initMargin)
	.def_readwrite("maintMargin",&OrderState::maintMargin)
	.def_readwrite("equityWithLoan",&OrderState::equityWithLoan)
	.def_readwrite("commission",&OrderState::commission)
	.def_readwrite("minCommission",&OrderState::minCommission)
	.def_readwrite("maxCommission",&OrderState::maxCommission)
	.def_readwrite("commissionCurrency",&OrderState::commissionCurrency)
	.def_readwrite("warningText",&OrderState::warningText)
	;

    class_<Order>("Order")
	// order identifier
	.def_readwrite("orderId",&Order::orderId)
	.def_readwrite("clientId",&Order::clientId)
	.def_readwrite("permId",&Order::permId)	
	// main order fields
	.def_readwrite("action",&Order::action)
	.def_readwrite("totalQuantity",&Order::totalQuantity)
	.def_readwrite("orderType",&Order::orderType)
	.def_readwrite("lmtPrice",&Order::lmtPrice)
	.def_readwrite("auxPrice",&Order::auxPrice)
	// extended order fields
	.def_readwrite("tif",&Order::tif) // "Time in Force" - DAY, GTC, etc.
	.def_readwrite("ocaGroup",&Order::ocaGroup) // one cancels all group name
	.def_readwrite("ocaType",&Order::ocaType) // 1 = CANCEL_WITH_BLOCK, 2 = REDUCE_WITH_BLOCK, 3 = REDUCE_NON_BLOCK
	.def_readwrite("orderRef",&Order::orderRef) // order reference
	.def_readwrite("transmit",&Order::transmit) // if false, order will be created but not transmited
	.def_readwrite("parentId",&Order::parentId) // Parent order Id, to associate Auto STP or TRAIL orders with the original order.
	.def_readwrite("blockOrder",&Order::blockOrder)
	.def_readwrite("sweepToFill",&Order::sweepToFill)
	.def_readwrite("displaySize",&Order::displaySize)
	.def_readwrite("triggerMethod",&Order::triggerMethod) // 0=Default, 1=Double_Bid_Ask, 2=Last, 3=Double_Last, 4=Bid_Ask, 7=Last_or_Bid_Ask, 8=Mid-point
	.def_readwrite("outsideRth",&Order::outsideRth)
	.def_readwrite("hidden",&Order::hidden)
	.def_readwrite("goodAfterTime",&Order::goodAfterTime) // Format: 20060505 08:00:00 {time zone}
	.def_readwrite("goodTillDate",&Order::goodTillDate) // Format: 20060505 08:00:00 {time zone}
	.def_readwrite("rule80A",&Order::rule80A) // Individual = 'I', Agency = 'A', AgentOtherMember = 'W', IndividualPTIA = 'J', AgencyPTIA = 'U', AgentOtherMemberPTIA = 'M', IndividualPT = 'K', AgencyPT = 'Y', AgentOtherMemberPT = 'N'
	.def_readwrite("allOrNone",&Order::allOrNone)
	.def_readwrite("minQty",&Order::minQty)
	.def_readwrite("percentOffset",&Order::percentOffset) // REL orders only
	.def_readwrite("overridePercentageConstraints",&Order::overridePercentageConstraints)
	.def_readwrite("trailStopPrice",&Order::trailStopPrice) // TRAILLIMIT orders only
	.def_readwrite("trailingPercent",&Order::trailingPercent)
	// financial advisors only
	.def_readwrite("faGroup",&Order::faGroup)
	.def_readwrite("faProfile",&Order::faProfile)
	.def_readwrite("faMethod",&Order::faMethod)
	.def_readwrite("faPercentage",&Order::faPercentage)
	// institutional (ie non-cleared) only
	.def_readwrite("openClose",&Order::openClose) // O=Open, C=Close
	.def_readwrite("origin",&Order::origin) // 0=Customer, 1=Firm
	.def_readwrite("shortSaleSlot",&Order::shortSaleSlot) // 1 if you hold the shares, 2 if they will be delivered from elsewhere. Only for Action="SSHORT
	.def_readwrite("designatedLocation",&Order::designatedLocation) // set when slot=2 only.
	.def_readwrite("exemptCode",&Order::exemptCode)
	// SMART routing only
	.def_readwrite("discretionaryAmt",&Order::discretionaryAmt)
	.def_readwrite("eTradeOnly",&Order::eTradeOnly)
	.def_readwrite("firmQuoteOnly",&Order::firmQuoteOnly)
	.def_readwrite("nbboPriceCap",&Order::nbboPriceCap)
	.def_readwrite("optOutSmartRouting",&Order::optOutSmartRouting)
	// BOX exchange orders only
	.def_readwrite("auctionStrategy",&Order::auctionStrategy) // AUCTION_MATCH, AUCTION_IMPROVEMENT, AUCTION_TRANSPARENT
	.def_readwrite("startingPrice",&Order::startingPrice)
	.def_readwrite("stockRefPrice",&Order::stockRefPrice)
	.def_readwrite("delta",&Order::delta)
	// pegged to stock and VOL orders only
	.def_readwrite("stockRangeLower",&Order::stockRangeLower)
	.def_readwrite("stockRangeUpper",&Order::stockRangeUpper)
	// VOLATILITY ORDERS ONLY
	.def_readwrite("volatility",&Order::volatility)
	.def_readwrite("volatilityType",&Order::volatilityType) // 1=daily, 2=annual
	.def_readwrite("deltaNeutralOrderType",&Order::deltaNeutralOrderType)
	.def_readwrite("deltaNeutralAuxPrice",&Order::deltaNeutralAuxPrice)
	.def_readwrite("deltaNeutralConId",&Order::deltaNeutralConId)
	.def_readwrite("deltaNeutralSettlingFirm",&Order::deltaNeutralSettlingFirm)
	.def_readwrite("deltaNeutralClearingAccount",&Order::deltaNeutralClearingAccount)
	.def_readwrite("deltaNeutralClearingIntent",&Order::deltaNeutralClearingIntent)
	.def_readwrite("deltaNeutralOpenClose",&Order::deltaNeutralOpenClose)
	.def_readwrite("deltaNeutralShortSale",&Order::deltaNeutralShortSale)
	.def_readwrite("deltaNeutralShortSaleSlot",&Order::deltaNeutralShortSaleSlot)
	.def_readwrite("deltaNeutralDesignatedLocation",&Order::deltaNeutralDesignatedLocation)
	.def_readwrite("continuousUpdate",&Order::continuousUpdate)
	.def_readwrite("referencePriceType",&Order::referencePriceType) // 1=Average, 2 = BidOrAsk
	// COMBO ORDERS ONLY
	.def_readwrite("basisPoints",&Order::basisPoints) // EFP orders only
	.def_readwrite("basisPointsType",&Order::basisPointsType) // EFP orders only
	// SCALE ORDERS ONLY
	.def_readwrite("scaleInitLevelSize",&Order::scaleInitLevelSize)
	.def_readwrite("scaleSubsLevelSize",&Order::scaleSubsLevelSize)
	.def_readwrite("scalePriceIncrement",&Order::scalePriceIncrement)
	.def_readwrite("scalePriceAdjustValue",&Order::scalePriceAdjustValue)
	.def_readwrite("scalePriceAdjustInterval",&Order::scalePriceAdjustInterval)
	.def_readwrite("scaleProfitOffset",&Order::scaleProfitOffset)
	.def_readwrite("scaleAutoReset",&Order::scaleAutoReset)
	.def_readwrite("scaleInitPosition",&Order::scaleInitPosition)
	.def_readwrite("scaleInitFillQty",&Order::scaleInitFillQty)
	.def_readwrite("scaleRandomPercent",&Order::scaleRandomPercent)
	// HEDGE ORDERS
	.def_readwrite("hedgeType",&Order::hedgeType) // 'D' - delta, 'B' - beta, 'F' - FX, 'P' - pair
	.def_readwrite("hedgeParam",&Order::hedgeParam) // 'beta=X' value for beta hedge, 'ratio=Y' for pair hedge
	// Clearing info
	.def_readwrite("account",&Order::account) // IB account
	.def_readwrite("settlingFirm",&Order::settlingFirm)
	.def_readwrite("clearingAccount",&Order::clearingAccount) // True beneficiary of the order
	.def_readwrite("clearingIntent",&Order::clearingIntent) // "" (Default), "IB", "Away", "PTA" (PostTrade)
	// ALGO ORDERS ONLY
	.def_readwrite("algoStrategy",&Order::algoStrategy)
	.def_readwrite("algoParams",&Order::algoParams)
	.def_readwrite("smartComboRoutingParams",&Order::smartComboRoutingParams)
	// What-if
	.def_readwrite("whatIf",&Order::whatIf)
	// Not Held
	.def_readwrite("notHeld",&Order::notHeld)
	.def_readwrite("orderComboLegs",&Order::orderComboLegs)
	;

    class_<Contract>("Contract")
	.def_readwrite("conId",                       &Contract::conId)
	.def_readwrite("symbol",                     &Contract::symbol)
	.def_readwrite("secType",                   &Contract::secType)
	.def_readwrite("expiry",                     &Contract::expiry)
	.def_readwrite("strike",                     &Contract::strike)
	.def_readwrite("right",                       &Contract::right)
	.def_readwrite("multiplier",             &Contract::multiplier)
	.def_readwrite("exchange",                 &Contract::exchange)
	.def_readwrite("primaryExchange",   &Contract::primaryExchange)
	.def_readwrite("currency",                 &Contract::currency)
	.def_readwrite("localSymbol",           &Contract::localSymbol)
	.def_readwrite("tradingClass",         &Contract::tradingClass)
	.def_readwrite("includeExpired",     &Contract::includeExpired)
	.def_readwrite("secIdType",               &Contract::secIdType)
	.def_readwrite("secId",                       &Contract::secId)
	.def_readwrite("comboLegsDescrip", &Contract::comboLegsDescrip)
	.def_readwrite("comboLegs",               &Contract::comboLegs)
	.def_readwrite("uncerComp",               &Contract::underComp)
	;

    class_<CommissionReport>("CommissionReport")
	.def_readwrite("execId",&CommissionReport::execId)
	.def_readwrite("commission",&CommissionReport::commission)
	.def_readwrite("currency",&CommissionReport::currency)
	.def_readwrite("realizedPNL",&CommissionReport::realizedPNL)
	.def_readwrite("yield",&CommissionReport::yield)
	.def_readwrite("yieldRedemptionDate",&CommissionReport::yieldRedemptionDate) // YYYYMMDD format
	;

    class_<ContractDetails>("ContractDetails")
	.def_readwrite("summary",&ContractDetails::summary)
	.def_readwrite("marketName",&ContractDetails::marketName)
	.def_readwrite("minTick",&ContractDetails::minTick)
	.def_readwrite("orderTypes",&ContractDetails::orderTypes)
	.def_readwrite("validExchanges",&ContractDetails::validExchanges)
	.def_readwrite("priceMagnifier",&ContractDetails::priceMagnifier)
	.def_readwrite("underConId",&ContractDetails::underConId)
	.def_readwrite("longName",&ContractDetails::longName)
	.def_readwrite("contractMonth",&ContractDetails::contractMonth)
	.def_readwrite("industry",&ContractDetails::industry)
	.def_readwrite("category",&ContractDetails::category)
	.def_readwrite("subcategory",&ContractDetails::subcategory)
	.def_readwrite("timeZoneId",&ContractDetails::timeZoneId)
	.def_readwrite("tradingHours",&ContractDetails::tradingHours)
	.def_readwrite("liquidHours",&ContractDetails::liquidHours)
	.def_readwrite("evRule",&ContractDetails::evRule)
	.def_readwrite("evMultiplier",&ContractDetails::evMultiplier)
	.def_readwrite("secIdList",&ContractDetails::secIdList) // Pointer
        // BOND values
	.def_readwrite("cusip",&ContractDetails::cusip)
	.def_readwrite("ratings",&ContractDetails::ratings)
	.def_readwrite("descAppend",&ContractDetails::descAppend)
	.def_readwrite("bondType",&ContractDetails::bondType)
	.def_readwrite("couponType",&ContractDetails::couponType)
	.def_readwrite("callable",&ContractDetails::callable)
	.def_readwrite("putable",&ContractDetails::putable)
	.def_readwrite("coupon",&ContractDetails::coupon)
	.def_readwrite("convertible",&ContractDetails::convertible)
	.def_readwrite("maturity",&ContractDetails::maturity)
	.def_readwrite("issueDate",&ContractDetails::issueDate)
	.def_readwrite("nextOptionDate",&ContractDetails::nextOptionDate)
	.def_readwrite("nextOptionType",&ContractDetails::nextOptionType)
	.def_readwrite("nextOptionPartial",&ContractDetails::nextOptionPartial)
	.def_readwrite("notes",&ContractDetails::notes)
	;

    class_<IBClientWrapper, boost::noncopyable>("IBClient")
	//interface
	.def("processMessages", &IBClient::processMessages)
	.def("runStrategy",     &IBClient::runStrategy, &IBClientWrapper::default_runStrategy)
	.def("setTimeOut",      &IBClient::setTimeOut)
	// helpers
	// Connection and Server
	.def("connect",&IBClient::connect)
	.def("disconnect",&IBClient::disconnect)
	.def("isConnected",&IBClient::isConnected)
	.def("reqGlobalCancel",&IBClient::reqGlobalCancel)
	.def("serverVersion",&IBClient::serverVersion)
	.def("TwsConnectionTime",&IBClient::TwsConnectionTime)
	.def("checkMessages",&IBClient::checkMessages)
	.def("setServerLogLevel",&IBClient::setServerLogLevel)
	.def("reqCurrentTime",&IBClient::reqCurrentTime)
	//::Market Data
	.def("reqMktData",&IBClient::reqMktData)
	.def("cancelMktData",&IBClient::cancelMktData)
	.def("calculateImpliedVolatility",&IBClient::calculateImpliedVolatility)
	.def("cancelCalculateImpliedVolatility",&IBClient::cancelCalculateImpliedVolatility)
	.def("calculateOptionPrice",&IBClient::calculateOptionPrice)
	.def("cancelCalculateOptionPrice",&IBClient::cancelCalculateOptionPrice)
	.def("reqMarketDataType",&IBClient::reqMarketDataType)
	// Order
	.def("placeOrder",&IBClient::placeOrder)
	.def("cancelOrder",&IBClient::cancelOrder)
	.def("reqOpenOrders",&IBClient::reqOpenOrders)
	.def("reqAutoOpenOrders",&IBClient::reqAutoOpenOrders)
	.def("reqAllOpenOrders",&IBClient::reqAllOpenOrders)
	.def("reqIds",&IBClient::reqIds)
	.def("exerciseOptions",&IBClient::exerciseOptions)
	// Account
	.def("reqAccountUpdates",&IBClient::reqAccountUpdates)
	// Excutions
	.def("reqExecutions",&IBClient::reqExecutions)
	// Contract Details
	.def("reqContractDetails",&IBClient::reqContractDetails)
	// Market Depth
	.def("reqMktDepth",&IBClient::reqMktDepth)
	.def("cancelMktDepth",&IBClient::cancelMktDepth)
	// News Bulletins
	.def("reqNewsBulletins",&IBClient::reqNewsBulletins)
	.def("cancelNewsBulletins",&IBClient::cancelNewsBulletins)
	// Finacial Advisors
	.def("reqManagedAccts",&IBClient::reqManagedAccts)
	.def("requestFA",&IBClient::requestFA)
	.def("replaceFA",&IBClient::replaceFA)
	.def("reqAccountSummary",&IBClient::reqAccountSummary)
	.def("cancelAccountSummary",&IBClient::cancelAccountSummary)
	.def("reqPositions",&IBClient::reqPositions)
	.def("cancelPositions",&IBClient::cancelPositions)
	// Historical Data
	.def("reqHistoricalData",&IBClient::reqHistoricalData)
	.def("cancelHistoricalData",&IBClient::cancelHistoricalData)
	// Market Scanner
	.def("reqScannerParameters",&IBClient::reqScannerParameters)
	.def("reqScannerSubscription",&IBClient::reqScannerSubscription)
	.def("cancelScannerSubscription",&IBClient::cancelScannerSubscription)
	// Real Time Bars
	.def("reqRealTimeBars",&IBClient::reqRealTimeBars)
	.def("cancelRealTimeBars",&IBClient::cancelRealTimeBars)
	// Fundamental Data
	.def("reqFundamentalData",&IBClient::reqFundamentalData)
	.def("cancelFundamentalData",&IBClient::cancelFundamentalData)
	//events
	.def("tickPrice",&IBClient::tickPrice, &IBClientWrapper::default_tickPrice)
	.def("tickSize",&IBClient::tickSize, &IBClientWrapper::default_tickSize)
	.def("tickOptionComputation",&IBClient::tickOptionComputation, &IBClientWrapper::default_tickOptionComputation)
	.def("tickGeneric",&IBClient::tickGeneric, &IBClientWrapper::default_tickGeneric)
	.def("tickString",&IBClient::tickString, &IBClientWrapper::default_tickString)
	.def("tickEFP",&IBClient::tickEFP, &IBClientWrapper::default_tickEFP)
	.def("orderStatus",&IBClient::orderStatus, &IBClientWrapper::default_orderStatus)
	.def("openOrder",&IBClient::openOrder, &IBClientWrapper::default_openOrder)
	.def("openOrderEnd",&IBClient::openOrderEnd, &IBClientWrapper::default_openOrderEnd)
	.def("winError",&IBClient::winError, &IBClientWrapper::default_winError)
	.def("connectionClosed",&IBClient::connectionClosed, &IBClientWrapper::default_connectionClosed)
	.def("updateAccountValue",&IBClient::updateAccountValue, &IBClientWrapper::default_updateAccountValue)
	.def("updatePortfolio",&IBClient::updatePortfolio, &IBClientWrapper::default_updatePortfolio)
	.def("updateAccountTime",&IBClient::updateAccountTime, &IBClientWrapper::default_updateAccountTime)
	.def("accountDownloadEnd",&IBClient::accountDownloadEnd, &IBClientWrapper::default_accountDownloadEnd)
	.def("nextValidId",&IBClient::nextValidId, &IBClientWrapper::default_nextValidId)
	.def("contractDetails",&IBClient::contractDetails, &IBClientWrapper::default_contractDetails)
	.def("bondContractDetails",&IBClient::bondContractDetails, &IBClientWrapper::default_bondContractDetails)
	.def("contractDetailsEnd",&IBClient::contractDetailsEnd, &IBClientWrapper::default_contractDetailsEnd)
	.def("execDetails",&IBClient::execDetails, &IBClientWrapper::default_execDetails)
	.def("execDetailsEnd",&IBClient::execDetailsEnd, &IBClientWrapper::default_execDetailsEnd)
	.def("error",&IBClient::error, &IBClientWrapper::default_error)
	.def("updateMktDepth",&IBClient::updateMktDepth, &IBClientWrapper::default_updateMktDepth)
	.def("updateMktDepthL2",&IBClient::updateMktDepthL2, &IBClientWrapper::default_updateMktDepthL2)
	.def("updateNewsBulletin",&IBClient::updateNewsBulletin, &IBClientWrapper::default_updateNewsBulletin)
	.def("managedAccounts",&IBClient::managedAccounts, &IBClientWrapper::default_managedAccounts)
	.def("receiveFA",&IBClient::receiveFA, &IBClientWrapper::default_receiveFA)
	.def("historicalData",&IBClient::historicalData, &IBClientWrapper::default_historicalData)
	.def("scannerParameters",&IBClient::scannerParameters, &IBClientWrapper::default_scannerParameters)
	.def("scannerData",&IBClient::scannerData, &IBClientWrapper::default_scannerData)
	.def("scannerDataEnd",&IBClient::scannerDataEnd, &IBClientWrapper::default_scannerDataEnd)
	.def("realtimeBar",&IBClient::realtimeBar, &IBClientWrapper::default_realtimeBar)
	.def("currentTime",&IBClient::currentTime, &IBClientWrapper::default_currentTime)
	.def("fundamentalData",&IBClient::fundamentalData, &IBClientWrapper::default_fundamentalData)
	.def("deltaNeutralValidation",&IBClient::deltaNeutralValidation, &IBClientWrapper::default_deltaNeutralValidation)
	.def("tickSnapshotEnd",&IBClient::tickSnapshotEnd, &IBClientWrapper::default_tickSnapshotEnd)
	.def("marketDataType",&IBClient::marketDataType, &IBClientWrapper::default_marketDataType)
	.def("commissionReport",&IBClient::commissionReport, &IBClientWrapper::default_commissionReport)
	.def("position",&IBClient::position, &IBClientWrapper::default_position)
	.def("positionEnd",&IBClient::positionEnd, &IBClientWrapper::default_positionEnd)
	.def("accountSummary",&IBClient::accountSummary, &IBClientWrapper::default_accountSummary)
	.def("accountSummaryEnd",&IBClient::accountSummaryEnd, &IBClientWrapper::default_accountSummaryEnd)
	//log system
	.def_readwrite("echo", &IBClient::echo)
	.def_readwrite("logFileName", &IBClient::logFileName)
	.def_readwrite("logPath", &IBClient::logPath)
	.def_readwrite("timeOut", &IBClient::timeOut)
	.def("addMessageLevel", &IBClient::addMessageLevel)
	//.def("rmMessageLevel", &IBClient::MessageLevel)
	.def("isMessageOn", &IBClient::isMessageOn)
	.def("getMessageLevel", &IBClient::getMessageLevel)
	.def("message", &IBClient::message)
	.def("logOn", &IBClient::logOn)
	.def("logOff", &IBClient::logOff)
	;
    
    enum_<IBClient::MSGLEVEL>("MsgLevel")
	.value("SYSERR", IBClient::SYSERR)
	.value("IBERROR", IBClient::IBERROR)
	.value("IBWARNING", IBClient::IBWARNING)
	.value("IBINFO", IBClient::IBINFO)
	.value("IBDEBUG", IBClient::IBDEBUG)
	.value("IBEVENT", IBClient::IBEVENT)
	;

    enum_<TickType>("TickType")
	.value("BID_SIZE", BID_SIZE)
	.value("BID", BID)
	.value("ASK", ASK)
	.value("ASK_SIZE", ASK_SIZE)
	.value("LAST", LAST)
	.value("LAST_SIZE", LAST_SIZE)
	.value("HIGH", HIGH)
	.value("LOW", LOW)
	.value("VOLUME", VOLUME)
	.value("CLOSE", CLOSE)
	.value("BID_OPTION_COMPUTATION", BID_OPTION_COMPUTATION)
	.value("ASK_OPTION_COMPUTATION", ASK_OPTION_COMPUTATION)
	.value("LAST_OPTION_COMPUTATION", LAST_OPTION_COMPUTATION)
	.value("MODEL_OPTION", MODEL_OPTION)
	.value("OPEN", OPEN)
	.value("LOW_13_WEEK", LOW_13_WEEK)
	.value("HIGH_13_WEEK", HIGH_13_WEEK)
	.value("LOW_26_WEEK", LOW_26_WEEK)
	.value("HIGH_26_WEEK", HIGH_26_WEEK)
	.value("LOW_52_WEEK", LOW_52_WEEK)
	.value("HIGH_52_WEEK", HIGH_52_WEEK)
	.value("AVG_VOLUME", AVG_VOLUME)
	.value("OPEN_INTEREST", OPEN_INTEREST)
	.value("OPTION_HISTORICAL_VOL", OPTION_HISTORICAL_VOL)
	.value("OPTION_IMPLIED_VOL", OPTION_IMPLIED_VOL)
	.value("OPTION_BID_EXCH", OPTION_BID_EXCH)
	.value("OPTION_ASK_EXCH", OPTION_ASK_EXCH)
	.value("OPTION_CALL_OPEN_INTEREST", OPTION_CALL_OPEN_INTEREST)
	.value("OPTION_PUT_OPEN_INTEREST", OPTION_PUT_OPEN_INTEREST)
	.value("OPTION_CALL_VOLUME", OPTION_CALL_VOLUME)
	.value("OPTION_PUT_VOLUME", OPTION_PUT_VOLUME)
	.value("INDEX_FUTURE_PREMIUM", INDEX_FUTURE_PREMIUM)
	.value("BID_EXCH", BID_EXCH)
	.value("ASK_EXCH", ASK_EXCH)
	.value("AUCTION_VOLUME", AUCTION_VOLUME)
	.value("AUCTION_PRICE", AUCTION_PRICE)
	.value("AUCTION_IMBALANCE", AUCTION_IMBALANCE)
	.value("MARK_PRICE", MARK_PRICE)
	.value("BID_EFP_COMPUTATION", BID_EFP_COMPUTATION)
	.value("ASK_EFP_COMPUTATION", ASK_EFP_COMPUTATION)
	.value("LAST_EFP_COMPUTATION", LAST_EFP_COMPUTATION)
	.value("OPEN_EFP_COMPUTATION", OPEN_EFP_COMPUTATION)
	.value("HIGH_EFP_COMPUTATION", HIGH_EFP_COMPUTATION)
	.value("LOW_EFP_COMPUTATION", LOW_EFP_COMPUTATION)
	.value("CLOSE_EFP_COMPUTATION", CLOSE_EFP_COMPUTATION)
	.value("LAST_TIMESTAMP", LAST_TIMESTAMP)
	.value("SHORTABLE", SHORTABLE)
	.value("FUNDAMENTAL_RATIOS", FUNDAMENTAL_RATIOS)
	.value("RT_VOLUME", RT_VOLUME)
	.value("HALTED", HALTED)
	.value("BID_YIELD", BID_YIELD)
	.value("ASK_YIELD", ASK_YIELD)
	.value("LAST_YIELD", LAST_YIELD)
	.value("CUST_OPTION_COMPUTATION", CUST_OPTION_COMPUTATION)
	.value("TRADE_COUNT", TRADE_COUNT)
	.value("TRADE_RATE", TRADE_RATE)
	.value("VOLUME_RATE", VOLUME_RATE)
	.value("LAST_RTH_TRADE", LAST_RTH_TRADE)
	.value("NOT_SET", NOT_SET)
	;
}
