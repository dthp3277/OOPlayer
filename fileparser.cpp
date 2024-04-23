#include "fileparser.h"


AudioFiles::AudioFiles(std::string dir) {
    directory = dir;
}

void AudioFiles::displayFiles() {
    int c = 1;
    std::string onlyfilename;
	for (auto i : filenames) {
        onlyfilename = getFileNameFromPath(i);
		std::cout << c << ". " << onlyfilename.substr(0, onlyfilename.size() - 4) << '\n';
        c++;
	}
	std::cout << std::flush;
}

void AudioFiles::getAudioFiles() {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().u8string();
            // Check if the file has a valid audio extension
            if (getFileExt(filename) == "wav" || getFileExt(filename) == "mp3") {
                filenames.push_back(directory + '/' + filename);
            }
        }
    }
}

void AudioFiles::select() {
    int i;
    std::cout << "Enter your choice of file: ";
    std::cin >> i;
    setPlay(i);
}

void AudioFiles::setPlay(int i = -1) {
    nowplaying = i;
}

std::string AudioFiles::getFileExt(std::string path) {
    size_t i = path.rfind('.', path.length());
    if (i != std::string::npos) {
        return(path.substr(i + 1, path.length() - i));
    }
    return("");
}

std::string AudioFiles::getFileNameFromPath(std::string path) {
    std::string filename;
    int i = path.length() - 1;
    int posSlash, posBackSlash, pos;
    posSlash = path.rfind('/');
    posBackSlash = path.rfind('\\');
    pos = (posBackSlash > posSlash) ? posBackSlash : posSlash;
    filename = path.substr(pos + 1, path.length() - pos);
    return filename;
}

bool AudioFiles::isDirectory() {
    //return std::filesystem::is_directory(directory); //which is better here?
    return std::filesystem::exists(directory);
}