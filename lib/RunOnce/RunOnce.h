#ifndef RUN_ONCE_H // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define RUN_ONCE_H 

//this class allows you to run a block of code once
//steps:
//in global scope write:
//RunOnce obj;
//in local scope, 
//while(obj.once()){  *write code block here*   }

class RunOnce {
  private:
    bool wasExecuted = false;

  public:
    bool once(){
        if(wasExecuted == false){
            wasExecuted = true;
            return true;
        } else {
            return false;
        }
    }
};

#endif