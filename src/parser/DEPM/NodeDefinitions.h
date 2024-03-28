/*
    Copyright (C) 2023 OpenPRA Initiative

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#define ATTR_SET "<xmlattr>"

#define DEPM_XML_TAG_MODEL "openepl" // error propagation language
#define DEPM_XML_TAG_EPC "epc" // error propagation command
#define DEPM_XML_TAG_CFC "cfc" // control flow command
#define DEPM_XML_TAG_OPENEPL "openepl"
#define DEPM_XML_TAG_ELEMENT "element"
#define DEPM_XML_TAG_FAILURE "failure"
#define DEPM_XML_TAG_DATA "data"
#define DEPM_XML_TAG_DATA_FLOW "data_flow"
#define DEPM_XML_TAG_CONTROL_FLOW "control_flow"

#define DEPM_XML_ATTR_NAME "name"
#define DEPM_XML_ATTR_VALUES "values"
#define DEPM_XML_ATTR_INITIAL_VALUE "initial_value"
#define DEPM_XML_ATTR_TO "to"
#define DEPM_XML_ATTR_FROM "from"
#define DEPM_XML_ATTR_INITIAL_ELEMENT "initial_element"
#define DEPM_XML_ATTR_INITIAL "initial"
#define DEPM_XML_ATTR_TIME "time"

#define DEPM_XML_ATTR_INTERESTING "interesting"
#define DEPM_XML_ATTR_INTERESTING_DATA_TYPE bool
