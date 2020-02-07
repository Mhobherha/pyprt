/**
 * ArcGIS CityEngine SDK Geometry Encoder for Python
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
 */

#include "PyCallbacks.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void PyCallbacks::addGeometry(const size_t initialShapeIndex, const double* vertexCoords,
                              const size_t vertexCoordsCount, const uint32_t* facesIndices, const uint32_t* faceCounts,
                              const size_t faceCountsCount) {

	if (vertexCoords != nullptr)
		mModels[initialShapeIndex].mVertices.insert(mModels[initialShapeIndex].mVertices.end(), vertexCoords,
		                                            vertexCoords + vertexCoordsCount);

	if (facesIndices != nullptr && faceCounts != nullptr) {
		mModels[initialShapeIndex].mFaces.reserve(mModels[initialShapeIndex].mFaces.size() + faceCountsCount);
		size_t vertexIndexBase = 0;
		for (uint32_t ind = 0; ind < faceCountsCount; ind++) {
			mModels[initialShapeIndex].mFaces.emplace_back(facesIndices + vertexIndexBase,
			                                               facesIndices + vertexIndexBase + faceCounts[ind]);
			vertexIndexBase += faceCounts[ind];
		}
	}
}

void PyCallbacks::addReports(const size_t initialShapeIndex, const wchar_t** stringReportKeys,
                             const wchar_t** stringReportValues, size_t stringReportCount,
                             const wchar_t** floatReportKeys, const double* floatReportValues, size_t floatReportCount,
                             const wchar_t** boolReportKeys, const bool* boolReportValues, size_t boolReportCount) {

	for (size_t i = 0; i < boolReportCount; i++) {
		py::object pyKey = py::cast(boolReportKeys[i]);
		mModels[initialShapeIndex].mCGAReport[pyKey] = boolReportValues[i];
	}

	for (size_t i = 0; i < floatReportCount; i++) {
		py::object pyKey = py::cast(floatReportKeys[i]);
		mModels[initialShapeIndex].mCGAReport[pyKey] = floatReportValues[i];
	}

	for (size_t i = 0; i < stringReportCount; i++) {
		py::object pyKey = py::cast(stringReportKeys[i]);
		mModels[initialShapeIndex].mCGAReport[pyKey] = stringReportValues[i];
	}
}
