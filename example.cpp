#include <iostream>
#include "rapidxml_adapter.hpp"

template < typename Ch = char >
void print_node(std::shared_ptr<rapidxml_adapter::xml_node<Ch>> _node, int _tab_num = 0)
{
    if (!_node)
    {
        return;
    }
    std::cout << std::string(_tab_num * 2, ' ') << "[" << _node->type() << "]" << _node->name() << ":" << _node->value();
    rapidxml_adapter::xml_attribute_list<Ch> attribute_list = _node->attributes();
    for(std::shared_ptr<rapidxml_adapter::xml_attribute<Ch>> attribute : attribute_list)
    {
        std::cout << " " << attribute->name() << "=" << attribute->value();
    }
    std::cout << std::endl;
    rapidxml_adapter::xml_node_list<Ch> node_list = _node->children();
    for (std::shared_ptr<rapidxml_adapter::xml_node<Ch>> node : node_list)
    {
        print_node(node, _tab_num + 1);
    }
}

int main()
{
	std::string xml_str = R"(
<application>
  <component name="UpdatesConfigurable">
    <enabledExternalComponentSources>
      <item value="Android SDK" />
    </enabledExternalComponentSources>
    <option name="externalUpdateChannels">
      <map>
        <entry key="Android SDK" value="Stable Channel" />
      </map>
    </option>
    <knownExternalComponentSources>
      <item value="Android SDK" />
    </knownExternalComponentSources>
    <option name="LAST_BUILD_CHECKED" value="IU-193.5233.102" />
    <option name="LAST_TIME_CHECKED" value="1611304045185" />
  </component>
</application>
	)";

    using namespace rapidxml_adapter;
    std::shared_ptr<xml_document<>> doc = std::make_shared<xml_document<>>();
    doc->parse<0>(xml_str);
    print_node<char>(doc);
	return 0;
}
