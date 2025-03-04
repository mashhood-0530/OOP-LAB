#include <iostream>
#include <string>
#include <vector>

// Base class for MediaFile
class MediaFile {
protected:
    std::string filePath;
    double size; // Size in MB

public:
    MediaFile(const std::string& path, double sz)
        : filePath(path), size(sz) {}

    virtual ~MediaFile() = default;

    virtual void play() {
        std::cout << "Playing media file: " << filePath << std::endl;
    }

    virtual void stop() {
        std::cout << "Stopping media file: " << filePath << std::endl;
    }

    virtual void display() const {
        std::cout << "File Path: " << filePath << ", Size: " << size << " MB" << std::endl;
    }
};

// Intermediate class for VisualMedia
class VisualMedia : virtual public MediaFile {
protected:
    std::string resolution; // e.g., "1920x1080"

public:
    VisualMedia(const std::string& path, double sz, const std::string& res)
        : MediaFile(path, sz), resolution(res) {}

    void display() const override {
        MediaFile::display();
        std::cout << "Resolution: " << resolution << std::endl;
    }
};

// Intermediate class for AudioMedia
class AudioMedia : virtual public MediaFile {
protected:
    int sampleRate; // e.g., 44100 Hz

public:
    AudioMedia(const std::string& path, double sz, int rate)
        : MediaFile(path, sz), sampleRate(rate) {}

    void display() const override {
        MediaFile::display();
        std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
    }
};

// Derived class for VideoFile (inherits from both VisualMedia and AudioMedia)
class VideoFile : public VisualMedia, public AudioMedia {
public:
    VideoFile(const std::string& path, double sz, const std::string& res, int rate)
        : MediaFile(path, sz), VisualMedia(path, sz, res), AudioMedia(path, sz, rate) {}

    void play() override {
        std::cout << "Playing video file: " << filePath << std::endl;
    }

    void display() const override {
        VisualMedia::display();
        std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
    }
};

// Derived class for ImageFile (inherits from VisualMedia)
class ImageFile : public VisualMedia {
public:
    ImageFile(const std::string& path, double sz, const std::string& res)
        : MediaFile(path, sz), VisualMedia(path, sz, res) {}

    void play() override {
        std::cout << "Cannot play image file: " << filePath << std::endl;
    }

    void display() const override {
        VisualMedia::display();
    }
};

// Derived class for AudioFile (inherits from AudioMedia)
class AudioFile : public AudioMedia {
public:
    AudioFile(const std::string& path, double sz, int rate)
        : MediaFile(path, sz), AudioMedia(path, sz, rate) {}

    void play() override {
        std::cout << "Playing audio file: " << filePath << std::endl;
    }

    void display() const override {
        AudioMedia::display();
    }
};

int main() {
    // Create objects of different media types
    VideoFile video("video.mp4", 250.5, "1920x1080", 44100);
    ImageFile image("image.jpg", 5.2, "1280x720");
    AudioFile audio("audio.mp3", 10.0, 48000);

    // Store pointers of type MediaFile*
    std::vector<MediaFile*> mediaLibrary = { &video, &image, &audio };

    // Demonstrate polymorphism and dynamic dispatch
    for (const auto& media : mediaLibrary) {
        media->play();
        media->stop();
        media->display();
        std::cout << "-------------------" << std::endl;
    }

    return 0;
}