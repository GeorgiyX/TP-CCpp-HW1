#ifndef TP_HW1_UTILS_H
#define TP_HW1_UTILS_H

#include <gtest/gtest.h>

extern const std::string OUT_STREAM_FILE;
extern const std::string IN_STREAM_FILE;

class IO_TEST : public testing::Test {
public:
    /**
     * Redirects the stream to the file.
     * @param file - the name of the file to which the current stream will be redirected.
     * @param stream - redirected stream.
     * @return original descriptor of the redirected stream.
     */
    int switchStreamToFile(const std::string &file, FILE *stream, fpos_t &pos);

    /**
     * Binds the stream to the passed descriptor
     * @param originalDescriptor
     * @param stream
     */
    void switchBackStream(int originalDescriptor, FILE *stream, fpos_t &pos);
    void flush();
    std::string getTestOutput();
    /**
     * Configures stdin to read the filePath from the passed path
     * @param filePath - path to the new stdin content
     */
    void setTestInput(const std::string &filePath);
    void clearTestOutput();
    void clearTestInput();

protected:
    void SetUp() override;
    void TearDown() override;

private:
    int _originalOutDescriptor = -1;
    int _originalInDescriptor = -1;
    fpos_t posOut;
    fpos_t posIn;
};

struct TestConfig {
    static size_t testSeed;
    static std::string testDataPath;
};

std::string file2string(const std::string &path);

#endif //TP_HW1_UTILS_H
