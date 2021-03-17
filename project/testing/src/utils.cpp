#include "utils.h"

const std::string OUT_STREAM_FILE = "custom_out.txt";
const std::string IN_STREAM_FILE = "custom_in.txt";

void IO_TEST::SetUp() {
    Test::SetUp();
    _originalOutDescriptor = IO_TEST::switchStreamToFile(OUT_STREAM_FILE, stdout);
    _originalInDescriptor = IO_TEST::switchStreamToFile(IN_STREAM_FILE, stdin);
}

void IO_TEST::TearDown() {
    Test::TearDown();
    IO_TEST::switchBackStream(_originalOutDescriptor, stdout);
    IO_TEST::switchBackStream(_originalInDescriptor, stdin);
}

int IO_TEST::switchStreamToFile(const std::string &file, FILE *stream) {
    fflush(stream);
    /* Get file descriptor, associated with original stdout */
    int currentStreamDescriptor = fileno(stream);
    if (currentStreamDescriptor == -1) {
        throw std::runtime_error("fileno");
    }
    /* Get copy of file descriptor, associated with original stream */
    int originalDescriptor = dup(currentStreamDescriptor);
    if (originalDescriptor == -1) {
        throw std::runtime_error("dup");
    }
    /* Close original stdout, open custom stream and associate stream with it: */
    FILE *filePtr = freopen(file.c_str(), "w", stream);
    if (!filePtr) {
        if (close(originalDescriptor)) {
            throw std::runtime_error("close + freopen");
        }
        throw std::runtime_error("freopen");
    }
    return currentStreamDescriptor;
}

void IO_TEST::switchBackStream(int originalDescriptor, FILE *stream) {
    fflush(stream);
    /* Get file descriptor, associated with current stream */
    int currentStreamDescriptor = fileno(stream);
    if (currentStreamDescriptor == -1) {
        throw std::runtime_error("fileno");
    }
    /* Close the current descriptor associated with stream and
     * associate it with the original descriptor */
    if (dup2(originalDescriptor, currentStreamDescriptor) == -1) {
        throw std::runtime_error("dup2");
    }
    if (close(originalDescriptor) == -1) {
        throw std::runtime_error("close");
    }
}

void IO_TEST::flush() {
    fflush(stdout);
    fflush(stdin);
}
