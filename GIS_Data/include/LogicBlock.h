#pragma once

#include <string>
#include <vector>
#include <functional>

namespace GIS_Data {
    class LogicBlock {
    private:
        std::string type;
        char transistor_type;

        std::vector<int> input_nets;
        std::vector<int> output_nets;
        std::vector<int> inner_blocks;

        std::function<std::vector<int>(const std::vector<int>&)> logic_func;

    public:
        LogicBlock(const std::string& t,
                const std::string& tr_t,
                const std::vector<int>& inputs,
                const std::vector<int>& outputs,
                const std::vector<int>& inner_blocks,
                std::function<std::vector<int>(const std::vector<int>&)> func) :
                type(t),
                transistor_type(tr_t[0]),
                input_nets(inputs),
                output_nets(outputs),
                inner_blocks(inner_blocks),
                logic_func(func) { }

        const std::vector<int> execute(const std::vector<int>& inputs) const { return logic_func(inputs); }

        const std::string getType() const { return type; }
        const char getTransistorType() const { return transistor_type; }
        const std::vector<int> getInputs() const { return input_nets; }
        const std::vector<int> getOutputs() const { return output_nets; }
        const std::vector<int> getInnerBlocks() const { return inner_blocks; }
        const std::function<std::vector<int>(const std::vector<int>&)> getFunc() const { return logic_func; }
    };
}
