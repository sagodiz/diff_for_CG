#ifndef LABELS_H
#define LABELS_H

namespace Labels {
  
  const std::string FILE_READ_ERROR = "Couldn't read file: ";
  const std::string FORMAT_NOT_FOUND_ERROR = "Format couldn't match the pre defined format.";
  const std::string UNINITIALIZED_RECORD = "Record couldn't be initialized. className packageName or methodName is missing.";
  const std::string METHOD_NOT_FOUND_ERROR = "Couldn't find method in the format.";
  const std::string COULD_NOT_WRITE_OUTPUT = "Couldn't write output file whilst making statistics.";
}

#endif