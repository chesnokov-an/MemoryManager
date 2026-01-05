#include <iostream>
#include <Memory/Manager.hpp>
#include <MVP/View.hpp>
#include <MVP/Presenter.hpp>

int main(){
    using namespace MVPNameSpace;

    Manager<1024> manager;
    Presenter presenter(manager);
    View view(presenter);

    return view.show();
}