#include "target.h"
#include "../langregistry.h"
#include "../consts.h"
#include "../utils.h"

#include <QDir>

Target::Target(const LangRegistry& langs, const QFileInfo& fi, const QString& tar) : lr(langs), target(tar) {
	changeFile(fi);
}

bool Target::changeFile(const QFileInfo& fi) {
	file = fi;
	buildsys = lr.getLang(file);
	return sanityCheck();
}

bool Target::sanityCheck() const {
	return file.exists() && lr.isBuildSys(buildsys);
}

QString Target::rm(const QString& key) {
	auto it = vars.find(key);
	if(it != vars.end()) {
		QString retval = it->second;
		vars.erase(it);
		return retval;
	}
	return "";
}

bool Target::build(const QDir& bd) const {
	const QString interpreter = dg_consts::STRING_DIR_BUILD+buildsys+"/run.rb";
	QStringList args;
	args.append(file.absoluteFilePath());
	args.append(bd.absolutePath());
	args.append(target);
	QString vars;
	for(auto it : this->vars)
		vars.append(it.first+'='+it.second+'\n');
	QByteArray arr = vars.toLocal8Bit(); //Okay, this is getting problematic.
	return dg_utils::runTool(interpreter.mid(1),&args,nullptr,&arr);
}

bool Target::clean(const QDir& bd) const {
	const QString interpreter = dg_consts::STRING_DIR_BUILD+buildsys+"/clean.rb";
	QStringList args;
	args.append(file.absoluteFilePath());
	args.append(bd.absolutePath());
	args.append("clean");
	QString vars;
	for(auto it : this->vars)
		vars.append(it.first+'='+it.second+'\n');
	QByteArray arr = vars.toLocal8Bit(); //Okay, this is getting problematic too.
	return dg_utils::runTool(interpreter.mid(1),&args,nullptr,&arr);
}