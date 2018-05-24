#include "../inc/Labels.h"

namespace Labels {
  
  const std::string FILE_READ_ERROR = "Couldn't read file: ";
  const std::string FORMAT_NOT_FOUND_ERROR = "Format couldn't match the pre defined format.";
  const std::string UNINITIALIZED_RECORD = "Record could not be initialized. className packageName or methodName is missing.";
  const std::string METHOD_NOT_FOUND_ERROR = "Could not find method in the format.";
  const std::string COULD_NOT_WRITE_OUTPUT = "Could not write output file whilst making statistics.";
  const std::string UNRECOGNIZED_SWITCH = "The given switch could not be found: ";
  const std::string COULD_NOT_WRITE_TSV = "Could not write tsv (tab separated file).";
  const std::string TOOL_HAS_MORE_THAN_ONE_REP = "Tool has more than one representation for method.";
  const std::string NO_LOADER_WERE_GIVEN = "No loader was given. Please give at least 1 loader.";
  const std::string COULD_NOT_WRITE_FILE_LIST = "Could not write list of tsv files.";
  const std::string CHP_TRANSFORMATION_OPTION_ERROR = "The transformation value is unrecognized.";
  const std::string ANONYM_CLASS_TRANSFORMATION_OPTION_UNKNOWN = "Transformation option for anonym classes is invalid.";
  const std::string WALA_NON_INNERCLASS_EXISTENCE = "Wala is among the nodes, but could not remove it as there is no '$'.";
  const std::string COULD_NOT_WRITE_GRAPHML = "Could not write graphml file";
  std::string PROJECT_NAME = "Default";
}