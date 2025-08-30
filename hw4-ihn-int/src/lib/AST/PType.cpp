#include "AST/PType.hpp"

const char *kTypeString[] = {"void", "integer", "real", "boolean", "string"};

// logical constness
const char *PType::getPTypeCString() const {
    if (!m_type_string_is_valid) {
        m_type_string += kTypeString[static_cast<size_t>(m_type)];

        if (m_dimensions.size() != 0) {
            m_type_string += " ";

            for (const auto &dim : m_dimensions) {
                m_type_string += "[" + std::to_string(dim) + "]";
            }
        }
        m_type_string_is_valid = true;
    }

    return m_type_string.c_str();
}

PTypeSharedPtr PType::getArrayReferenceType(size_t dims) const {
    PTypeSharedPtr type = std::make_shared<PType>(m_type);
    type->m_dimensions =
        std::vector<uint64_t>(m_dimensions.begin() + dims, m_dimensions.end());
    return type;
}

bool PType::operator==(const PType &p_type) const {
    // Check scalar type
    if (this->isInteger() && p_type.isInteger())
        return true;
    if (this->isReal() && p_type.isReal())
        return true;
    if (this->isBool() && p_type.isBool())
        return true;
    if (this->isString() && p_type.isString())
        return true;

    // Check array type
    if (this->m_type == p_type.m_type && 
        this->m_dimensions.size() == p_type.m_dimensions.size()) {
        // Check all the dimension
        for (size_t i = 0; i < m_dimensions.size(); i++) {
            if (this->m_dimensions[i] != p_type.m_dimensions[i]) 
                return false;
        }
        return true;
    }
    return false;
}

bool PType::operator>(const PType &p_type) const {
    if (this->isReal() && p_type.isInteger())
        return true;
    else return false;
}

