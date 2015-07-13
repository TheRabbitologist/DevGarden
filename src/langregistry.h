#ifndef LANGREFCOUNT_H
#define LANGREFCOUNT_H

#include <map>
#include <QString>

class LangRegistry {
	static const QString DIR;
	static const QString EMPTY;
	struct Entry {Entry() {refs = 0;} size_t refs;};
	std::map<QString,QString> fileexts;
	std::map<QString,Entry> langs;
public:
	LangRegistry();

	//Tests for known mappings.
	inline bool knowsExt(const QString& fileext) const {return fileexts.count(fileext);}
	inline bool knowsLang(const QString& lang) const {return langs.count(lang);}

	/**
	 * @brief Test if the registry has loaded a language for a certain file extension.
	 */
	bool ready(const QString& fileext) const;

	/**
	 * Loads a language by file extension, increments the reference count for it, and returns the language name.
	 * To be used when a project needs to open a file of an unexpected language.
	 */
	const QString& load(const QString& fileext);

	//Reference counting, to be incremented per PROJECT, not PER FILE!
	bool add(const QStringList& lang);
	bool rem(const QStringList& lang);

	inline size_t countRefs(const QString& lang) const {return langs.at(lang).refs;}
	inline size_t countLanguages() const {return langs.size();}
	inline size_t countFileexts() const {return fileexts.size();}

};

#endif // LANGREFCOUNT_H