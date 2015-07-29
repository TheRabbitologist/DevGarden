#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include "envmacros.h"
#include "configentry.h"

#include <vector>

#if defined(DG_ENV_MACOS)
	#define DG_CONFIG_PREFIX_GLOBAL "/Library/Application Support/"
	#define DG_CONFIG_PREFIX_LOCAL  "Library/Application Support/"
#elif defined(DG_ENV_WINDOZE)
	#define DG_CONFIG_PREFIX_GLOBAL "ProgramData/"
	#define DG_CONFIG_PREFIX_LOCAL  "AppData/Roaming/"
#elif defined(DG_ENV_UNIX)
	#define DG_CONFIG_PREFIX_GLOBAL "usr/share/"
	#define DG_CONFIG_PREFIX_LOCAL  "."
	#define DG_CONFIG_PREFIX_LOCAL_NOCD
#else
	#define DG_CONFIG_PREFIX_GLOBAL "/"
	#define DG_CONFIG_PREFIX_LOCAL  ""
	#define DG_CONFIG_PREFIX_LOCAL_NOCD
#endif

class QFile;
class QFileInfo;
class QDir;

#include <QString>

#include <set>
#include <map>

/**
 * @brief Stores one file worth of configuration entires.
 */
class ConfigFile {
public:
	using Values = std::vector<ConfigEntry*>;
private:
	using EntryList = std::map<QString,Values>;
	QString name;
	EntryList entries;
public:
	ConfigFile() {};
	ConfigFile(const QString& name);
	ConfigFile(QFile* f);
	~ConfigFile() {for (auto& val : entries) {for (auto& ent : val.second) delete ent;}}
	inline bool isLoaded() const {return !entries.empty();}
	inline ConfigFile& setName(const QString& name) {this->name = name; return *this;}
	inline const QString& getName() const {return name;}

	inline EntryList::iterator begin() {return entries.begin();}
	inline EntryList::iterator end() {return entries.begin();}

	inline EntryList::const_iterator cbegin() const {return entries.cbegin();}
	inline EntryList::const_iterator cend() const {return entries.cend();}

	inline size_t size() const {return entries.size();}
	size_t count(const QString& name) const;
	Values* get(const QString& name); //Do not call on DGFamily.
	ConfigEntry* at(const QString& name, size_t index = 0);

	bool insert(ConfigEntry* ce);
	Values remove(const QString& name);
	void erase(const QString& name);
};

void makeConfigDirs();
bool runTool(const QString& name, QStringList* args = nullptr, QByteArray* out = nullptr, QByteArray* in = nullptr);
ConfigEntry* getConfigEntry(QFile* ptr);
QFileInfo* getUtilityFile(const QString& name);
QFile* getUtilityFileRead(const QString& name);
QFile* getUtilityFileWrite(const QString& name);
std::set<QString> getConfigDirs(const QString& name); //Gets unique subdirectories of a provided config directory, across both config folders.

#endif // CONFIGLOADER_H
