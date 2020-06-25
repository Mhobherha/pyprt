/**
 * PyPRT - Python Bindings for the Procedural Runtime (PRT) of CityEngine
 *
 * Copyright (c) 2012-2020 Esri R&D Center Zurich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * A copy of the license is available in the repository's LICENSE file.
 */

#pragma once

#include "types.h"

#include "prt/API.h"
#include "prt/LogHandler.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <cstdlib>
#include <filesystem>
#include <ostream>
#include <string>

namespace py = pybind11;

namespace pcu {

enum class RunStatus : uint8_t { DONE = EXIT_SUCCESS, FAILED = EXIT_FAILURE, CONTINUE = 2 };

bool getResolveMap(const std::filesystem::path& rulePackagePath, ResolveMapPtr* resolveMap);
std::wstring getRuleFileEntry(const prt::ResolveMap* resolveMap);

AttributeMapPtr createAttributeMapFromPythonDict(const py::dict& args, prt::AttributeMapBuilder& bld);
AttributeMapPtr createValidatedOptions(const std::wstring& encID, const AttributeMapPtr& unvalidatedOptions);

template <typename C>
std::vector<const C*> toPtrVec(const std::vector<std::basic_string<C>>& sv) {
	std::vector<const C*> pv(sv.size());
	std::transform(sv.begin(), sv.end(), pv.begin(), [](const auto& s) { return s.c_str(); });
	return pv;
}

template <typename C, typename D>
std::vector<const C*> toPtrVec(const std::vector<std::unique_ptr<C, D>>& sv) {
	std::vector<const C*> pv(sv.size());
	std::transform(sv.begin(), sv.end(), pv.begin(), [](const std::unique_ptr<C, D>& s) { return s.get(); });
	return pv;
}

std::wstring removeStylePrefix(const std::wstring& fullName);

/**
 * string and URI helpers
 */
using URI = std::string;

std::string toOSNarrowFromUTF16(const std::wstring& osWString);
std::wstring toUTF16FromOSNarrow(const std::string& osString);
std::wstring toUTF16FromUTF8(const std::string& utf8String);
std::string toUTF8FromOSNarrow(const std::string& osString);
std::string percentEncode(const std::string& utf8String);
URI toFileURI(const std::string& p);

/**
 * XML helpers
 */
std::string objectToXML(const prt::Object* obj);
RunStatus codecInfoToXML(const std::string& infoFilePath);

/**
 * default initial shape geometry (a quad)
 */
namespace quad {
const double vertices[] = {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0};
const size_t vertexCount = 12;
const uint32_t indices[] = {0, 1, 2, 3};
const size_t indexCount = 4;
const uint32_t faceCounts[] = {4};
const size_t faceCountsCount = 1;
} // namespace quad

std::filesystem::path getModuleDirectory();

} // namespace pcu
