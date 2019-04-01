#ifndef __ascii_toupper
#include <ctype>
#ifndef __ascii_toupper
#define __ascii_toupper(c)   ( (((c) >= 'a') && ((c) <= 'z')) ? ((c) - 'a' + 'A') : (c) )
#endif
#endif
#ifndef strcmp
#include <cstring>
#endif
#define GCR_DB_EVENT_bCHANGE 1 << 1 // will be called before a value gets changed                | specification includes variable name
#define GCR_DB_EVENT_bDEFINE 1 << 2 // will be called before a value gets set for the first time | specification includes variable name
#define GCR_DB_EVENT_bGET    1 << 3 // will be called before the get() function is called       was  | specification includes variable name
#define GCR_DB_EVENT_bTHROW  1 << 4 // will be called before a exception is throwed              | specification includes exception.what()

#define GCR_DB_EVENT_aCHANGE 1 << 5 // will be called after a value gets changed                 | specification includes variable name
#define GCR_DB_EVENT_aDEFINE 1 << 6 // will be called after a value gets set for the first time  | specification includes variable name

#include <exception>
#include <deque>
#include <fstream>
namespace gcr {
	class not_found;
	class bad_file;
	class invalid_csv_structure;
	class database;
	class database_parse;
	struct decimal;

	class not_found : public std::exception {
	public:
		not_found() noexcept : std::exception("not found", 1) { }
	private:
		not_found(char const * const _Message) noexcept : exception(_Message, 1) { }
	};

	class bad_file : public std::exception {
	public:
		bad_file() noexcept : std::exception("bad file", 1) { }
	private:
		bad_file(char const * const _Message) noexcept : exception(_Message, 1) { }
	};

	class invalid_csv_structure : public std::exception {
	public:
		invalid_csv_structure() noexcept : std::exception("invald csv structure", 1) { }
	private:
		invalid_csv_structure(char const * const _Message) noexcept : exception(_Message, 1) { }
	};
	
	class database {
	private:
		struct entry {
			void * data;
			std::string description;
		};

		struct subscriber {
			uint64_t type;
			void (*onEvent) (std::string);
		};

		std::deque<entry> entries;
		std::deque<subscriber> subscribers;

		bool sorted = false;
		bool autoDefrag = false;

		std::string toUpper(std::string text) {
			for (uint64_t i = 0; i < text.length(); i++)
				text[i] = __ascii_toupper(text[i]);
			return text;
		}

		void handleEvent(uint64_t type, std::string specification) {
			for (subscriber s : subscribers) {
				if (s.type & type) {
					s.onEvent(specification);
				}
			}
		}

	public:
		// https://www.geeksforgeeks.org/sorting-strings-using-bubble-sort-2/
		// the get() function will act about 1.5x faster if the data is sorted,
		// because of "smart algorithms"
		void defrag() {
			for (uint64_t i = 0; i < entries.size() - 1; i++) {
				for (uint64_t j = i + 1; j < entries.size(); j++) {
					if (strcmp(entries[i].description.c_str(), entries[j].description.c_str()) > 0) {
						std::swap(entries[j], entries[i]);
					}
				}
			}
			sorted = true;
		}

		database() { }

		~database() {
			entries.~deque();
		}

		inline void setAutoDefrag(bool value) { autoDefrag = value; }

		void * get(std::string description) {
			handleEvent(GCR_DB_EVENT_bGET, description);
			description = database::toUpper(description);
			int start = 0;
			if (sorted) {
				if (entries[entries.size() / 2].description[0] < description[0])
					start = entries.size() / 2;
			}

			for (uint64_t i = start; i < entries.size(); i++) {
				if (entries[i].description == description)
					return entries[i].data;
			}
			handleEvent(GCR_DB_EVENT_bTHROW, gcr::not_found().what());
			throw gcr::not_found();
		}

		template<typename T>
		void set(std::string description, T data) {
			description = gcr::database::toUpper(description);
			for (uint64_t i = 0; i < entries.size(); i++) {
				if (entries[i].description == description) {
					handleEvent(GCR_DB_EVENT_bCHANGE, description);
					entries[i].data = reinterpret_cast<void *>(data);
					handleEvent(GCR_DB_EVENT_aCHANGE, description);
					return;
				}
			}
			sorted = false;
			handleEvent(GCR_DB_EVENT_bDEFINE, description);
			entries.push_back(entry{ reinterpret_cast<void *>(data), description });
			handleEvent(GCR_DB_EVENT_aDEFINE, description);
			if (autoDefrag == true)
				defrag();
		}

		void subscribeEvent(uint64_t event, void(*function)(std::string)) {
			subscribers.push_back({ event, function });
		}

		void printDebugData() {
			int varsToPrint = 20;
			std::cout << "entries vector size: " << entries.size() << "\t/\t" << entries.max_size() << std::endl;
			std::cout << "auto defragment: " << (autoDefrag == true ? "enabled" : "disabled") << std::endl;
			std::cout << std::endl;
			//std::cout << entries.max_size
			// print all variables with their name and their data represented as char *
			int longestDescriptionLength = 0;
			for (int i = 0; i < varsToPrint; i++) {
				entry e = entries[i];
				if (e.description.length() > longestDescriptionLength)
					longestDescriptionLength = e.description.length();
			}
			longestDescriptionLength++;
			std::string inbetweenJunk = "";
			std::string splitJunk = "";
			for (int i = 0; i < longestDescriptionLength; i++) {
				inbetweenJunk += " ";
				splitJunk += "-";
			}
			
			inbetweenJunk += "| ";
			splitJunk += "----+------";
			std::cout << "data stored:\nname" + inbetweenJunk + "data" << std::endl;
			std::cout << splitJunk << std::endl;
			inbetweenJunk += "\b\b    | ";
			for (int i = 0; i < varsToPrint; i++) {
				entry e = entries[i];
				std::cout << inbetweenJunk << reinterpret_cast<char *>(e.data) << "\r" << e.description << "\n";
			}
			if (varsToPrint < entries.size())
				std::cout << splitJunk << "\b\b\b\b\b\b      \nand\t" << entries.size() - 10 << "\tmore entries...";
		}
	};

	static class database_parse {
	private:
		// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#answer-46931770
		static std::deque<std::string> split(std::string s, std::string delimiter) {
			size_t pos_start = 0, pos_end, delim_len = delimiter.length();
			std::string token;
			std::deque<std::string> res;

			while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
				token = s.substr(pos_start, pos_end - pos_start);
				pos_start = pos_end + delim_len;
				res.push_back(token);
			}

			res.push_back(s.substr(pos_start));
			return res;
		}

		static bool isNumeric(std::string s) {
			std::string allowedChars = "-0123456789";
			for (uint64_t i = 0; i < s.length(); i++) {
				bool numeric = false;
				for (int j = 0; j < allowedChars.length(); j++)
					if (s[i] == allowedChars[j])
						numeric = true;
				if (numeric == false)
					return false;
			}
			return true;
		}

		static std::string toUpper(std::string s) {
			for (uint64_t i = 0; i < s.length(); i++)
				s[i] = __ascii_toupper(s[i]);
			return s;
		}

	public:
		static void parse_csv(gcr::database * db, std::string file, std::string delimiter) {
			std::ifstream ifs(file);
			if (!ifs.is_open() || ifs.bad())
				throw gcr::bad_file();

			while (!ifs.eof()) {
				char cLine[512];
				ifs.getline(cLine, 512);
				if (strcmp(cLine, "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ") > 1)
					continue;
				std::string sLine(cLine);
				std::deque<std::string> parsedLine = gcr::database_parse::split(sLine, delimiter);

				if(parsedLine.size() < 2)
					throw gcr::invalid_csv_structure();

				db->set(parsedLine[1], const_cast<char *>(parsedLine[1].c_str()));
			}

		}
	};

	struct decimal {
	private:
		unsigned char precision = 7;
		uint64_t multiplicator = pow(10, precision);
		uint64_t value = 0;

		void set(double val) {
			value = (double)multiplicator * val;
		}

		double get() {
			return (double)value / (double)multiplicator;
		}

	public:
		decimal() {}
		decimal(double x) { set(x); }
		decimal(decimal & x) { precision = x.precision; multiplicator = x.multiplicator; value = x.value; }
		decimal(decimal * x) { precision = x->precision; multiplicator = x->multiplicator; value = x->value; }

		// set precision where x represents the numbers decimal places
		void setPrecision(unsigned char x) {
			precision = x;
			multiplicator = pow(10, x);
		}

		decimal & operator=(decimal & x) noexcept {
			precision = x.precision;
			multiplicator = x.multiplicator;
			value = x.value;
		}

		inline decimal & operator=(double x) noexcept { set(x); return *this; }
		inline operator double() noexcept { return get(); }
		inline decimal & operator+=(double x) noexcept { set(get() + x); return *this; }
		inline decimal & operator-=(double x) noexcept { set(get() - x); return *this; }
		inline decimal & operator*=(double x) noexcept { set(get() * x); return *this; }
		inline decimal & operator/=(double x) noexcept { set(get() / x); return *this; }
	};

}