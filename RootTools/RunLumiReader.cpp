#include "RunLumiReader.h"
#include <boost/property_tree/json_parser.hpp>
#include "Toolbox/StringTools.h"
#include "Toolbox/IOHelper.h"

void readLumiFilter(const std::string json, std::map<run_id, std::vector<std::pair<lumi_id, lumi_id> > > &lumifilter)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_json(json, pt);
	for (ptree::const_iterator itRun = pt.begin(); itRun != pt.end(); ++itRun)
	{
		run_id run = parse<run_id>(itRun->first);
		for (ptree::const_iterator itLumiList = itRun->second.begin(); itLumiList != itRun->second.end(); ++itLumiList)
		{
			lumi_id lumi_low = 0, lumi_high = 0;
			for (ptree::const_iterator itLumiRange = itLumiList->second.begin(); itLumiRange != itLumiList->second.end(); ++itLumiRange)
			{
				if (lumi_low == 0)
					lumi_low = parse<lumi_id>(itLumiRange->second.data());
				else if (lumi_high == 0)
					lumi_high = parse<lumi_id>(itLumiRange->second.data());
			}
			lumifilter[run].push_back(std::make_pair(lumi_low, lumi_high));
		}
	}
}

RunLumiSelector::RunLumiSelector(const run_id _passRun, const std::string json)
	: passRun(_passRun)
{
	if (json != "")
		readLumiFilter(json, lumifilter);
}

std::ostream &operator<<(std::ostream &os, const std::pair<lumi_id, lumi_id> &p)
{
	return os << p.first << "-" << p.second;
}

std::ostream &operator<<(std::ostream &os, RunLumiSelector &m)
{
	os << "Accepted runs / lumis:" << std::endl << m.lumifilter << std::endl
		<< "All runs <= " << m.passRun << " are automatically accepted" << std::endl;
	return os;
}