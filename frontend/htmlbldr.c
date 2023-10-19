// read html code
// read css code
// read js code

#include <iostream>
#include <queue>
#include <string>

int main() {
    int limit;
    std::cout << "Enter the limit for identifier length: ";
    std::cin >> limit;

    if (limit < 1) {
        std::cout << "Limit must be at least 1." << std::endl;
        return 1;
    }

    generate_names(limit);

    return 0;
}


int numlimit(int lim) {
	uint64_t allowed = 54;
	for (int i = 0; i < 255; ++i) {
		allowed <<= 6;
		if (allowed>lim) return allowed;
	}

	return 255;
}


std::vector<std::string> generateLegalNames(size_t limit)
{
	// instead of queues what if we use
    std::queue<std::string> q;
    std::vector<std::string> out;

    for (char c = 'a'; c <= 'z'; ++c) {
        q.push(std::string(1, c));
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        q.push(std::string(1, c));
    }
    q.push("_");
    q.push("-");

    size_t count = 0;
    while (!q.empty() && count < limit) {
        std::string name = q.front();
        q.pop();
        std::cout << name << std::endl;
        
        out.push_back(name);
        ++count;


        for (char c = 'a'; c <= 'z'; ++c) {
            q.push(name + c);
        }
        for (char c = 'A'; c <= 'Z'; ++c) {
            q.push(name + c);
        }
        for (char c = '0'; c <= '9'; ++c) {
            q.push(name + c);
        }
        q.push(name + "_");
        q.push(name + "-");

    }

    return out;
}


int generate() {
	char allowedChars[] = {'-', '_', 'a', 'b', 'c', 'd',
						   'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
						   'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
						   'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
						   'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
						   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
						   'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
						   '0', '1', '2', '3', '4', '5',
						   '6', '7', '8', '9', };

	for (int i = 0; i < 255; ++i) {
		allowed <<= 6;
		if (allowed>lim) return allowed;
	}




	// generate names
	for (int j = 0; i < 54; ++j) {
		// first characters
	}

	for (int i = 0; i < (allowed - 1); ++i) {
		// generate another one

		for (int j = 0; j < 64; ++j) {
			// allowable characters
		}
	}

	return 255;
}


struct reference_example
{

};

struct references
{
	int html;
	int css;
	int js;

	// also have reference list to expand
};

// have a reference counter for html, css, js uses
hat_trie<char, references> reflist;


// if something exists in one of these only, then keep it.
// check references one by one,
// now begin rewrite with code

// see which classes and ids are most used
// most used ones get rewritten with an easier id


for (x in references) {
	auto val = it.value();
	if (key)
}

// simplify places in CSS where certain IDs and classes are never used
