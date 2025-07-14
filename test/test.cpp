class base{
    public:
     int var1;
     base* pointer;

     void setVar1(int v){
         var1=v;
     }
     ~base() = default; // Default destructor
};

class derived:public base{
    public:
     float var2;
     
     void setVar2(float v){
         var2=v;
     }
     int getVar1(){
         return var1;
     }
     int getVar2(){
         return var2;
     }
};

float func(base* b){
    //derived* d = dynamic_cast<derived*>(b);
   // return d->getVar1();
}
