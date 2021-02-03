#include <iostream>
#include <sstream>
#include "rapidxml_adapter.hpp"
#include "rapidxml_adapter_print.hpp"

int main()
{
  using namespace rapidxml_adapter;
  using namespace std;
  std::shared_ptr<xml_document<>> doc = std::make_shared<xml_document<>>();
  {
    std::shared_ptr<xml_node<>> root = std::make_shared<xml_node<>>(rapidxml::node_element);
    root->name("root");
    {
      // attributes 3 4 1 2
      std::shared_ptr<xml_attribute<>> root_attr1 = std::make_shared<xml_attribute<>>();
      root_attr1->name("attr1");
      root_attr1->value("1");
      root->append_attribute(root_attr1);
      
      std::shared_ptr<xml_attribute<>> root_attr2 = std::make_shared<xml_attribute<>>();
      root_attr2->name("attr2");
      root_attr2->value("2");
      root->append_attribute(root_attr2);
      
      std::shared_ptr<xml_attribute<>> root_attr3 = std::make_shared<xml_attribute<>>();
      root_attr3->name("attr3");
      root_attr3->value("3");
      root->prepend_attribute(root_attr3);

      std::shared_ptr<xml_attribute<>> root_attr4 = std::make_shared<xml_attribute<>>();
      root_attr4->name("attr4");
      root_attr4->value("4");
      root->insert_attribute(root_attr1, root_attr4);
    }
    {
      // roles
      std::shared_ptr<xml_node<>> roles = std::make_shared<xml_node<>>(rapidxml::node_element);
      roles->name("roles");
      {
        //roles zhangsan lisi wanger mazi
        std::shared_ptr<xml_node<>> role1 = std::make_shared<xml_node<>>(rapidxml::node_element);
        role1->name("role");
        role1->value("wanger");
        roles->append_node(role1);

        std::shared_ptr<xml_node<>> role2 = std::make_shared<xml_node<>>(rapidxml::node_element);
        role2->name("role");
        role2->value("mazi");
        roles->append_node(role2);
        
        std::shared_ptr<xml_node<>> role3 = std::make_shared<xml_node<>>(rapidxml::node_element);
        role3->name("role");
        role3->value("zhangsan");
        roles->prepend_node(role3);
        
        std::shared_ptr<xml_node<>> role4 = std::make_shared<xml_node<>>(rapidxml::node_element);
        role4->name("role");
        role4->value("lisi");
        roles->insert_node(role1, role4);
      }
      root->append_node(roles);
    }
    {
      // items
      std::shared_ptr<xml_node<>> items = std::make_shared<xml_node<>>(rapidxml::node_element);
      items->name("items");
      {
        //weapon
        std::shared_ptr<xml_node<>> weapon = std::make_shared<xml_node<>>(rapidxml::node_element);
        weapon->name("weapon");
        weapon->value("qinggang");
        items->append_node(weapon);
      }
      {
        //cloth
        std::shared_ptr<xml_node<>> cloth = std::make_shared<xml_node<>>(rapidxml::node_element);
        cloth->name("cloth");
        cloth->value("fengyi");
        items->append_node(cloth);
      }
      root->append_node(items);
    }
    doc->append_node(root);
  }

  stringstream ss;
  ss << doc;
  cout << ss.str() << endl;

  std::shared_ptr<xml_document<>> doc2 = std::make_shared<xml_document<>>();
  doc2->parse<0>(ss.str());
  assert(doc2->first_node()->name() == "root");
  assert(doc2->first_node()->attributes().size() == 4);
  assert(doc2->first_node()->children().size() == 2);
  assert(doc2->first_node()->first_attribute()->value() == "3");
  assert(doc2->first_node()->last_attribute()->value() == "2");
  assert(doc2->first_node()->first_attribute("attr1")->value() == "1");
  assert(doc2->first_node()->attributes("attr1").size() == 1);
  assert(doc2->first_node()->first_attribute("attr2")->value() == "2");
  assert(doc2->first_node()->attributes("attr2").size() == 1);
  assert(doc2->first_node()->first_attribute("attr3")->value() == "3");
  assert(doc2->first_node()->attributes("attr3").size() == 1);
  assert(doc2->first_node()->first_attribute("attr4")->value() == "4");
  assert(doc2->first_node()->attributes("attr4").size() == 1);
  assert(doc2->first_node()->first_node()->name() == "roles");
  assert(doc2->first_node()->last_node()->name() == "items");
  assert(doc2->first_node()->first_node("roles")->name() == "roles");
  assert(doc2->first_node()->first_node("items")->name() == "items");
  assert(doc2->first_node()->first_node()->children().size() == 4);
  assert(doc2->first_node()->first_node()->children("role").size() == 4);
  assert(doc2->first_node()->first_node()->first_node()->name() == "role");
  assert(doc2->first_node()->first_node()->first_node()->value() == "zhangsan");
  assert(doc2->first_node()->first_node()->last_node()->name() == "role");
  assert(doc2->first_node()->first_node()->last_node()->value() == "mazi");
  assert(doc2->first_node()->last_node()->children().size() == 2);
  assert(doc2->first_node()->last_node()->children("weapon").size() == 1);
  assert(doc2->first_node()->last_node()->children("cloth").size() == 1);
  assert(doc2->first_node()->last_node()->first_node()->name() == "weapon");
  assert(doc2->first_node()->last_node()->first_node()->value() == "qinggang");
  assert(doc2->first_node()->last_node()->last_node()->name() == "cloth");
  assert(doc2->first_node()->last_node()->last_node()->value() == "fengyi");

  stringstream ss2;
  ss2 << doc2;
  cout << ss2.str() << endl;

  assert(ss.str() == ss2.str());

  doc2->clear();
  stringstream ss3;
  ss3 << doc2;
  cout << ss3.str() << endl;
  assert(ss3.str() == "\n");
}
