
#ifndef DATA_BUFFER_HPP // name of file, all caps (this is called a guard - it must be 
                // different for each header file, actual name is irrelevant)
#define DATA_BUFFER_HPP
//class that implements a fixed capacity queue
//the last "size" data values are contained within DataBuffer
//to access the nth last variable put in, use get(n);
template <class T>
class DataBuffer{
    private:
        T* array;
        int size;
        int root;
        T init;
    public:
        //give the size of the databuffer
        DataBuffer(int size, T init){
            this->size = size;
            this->init = init;
            array = new T[size];
            reset(init);
        }
        
        //put one data value into buffer
        void add(T data){
            //update the location of the root
            root--; 
            if(root < 0){ root += size; }
            array[root] = data;
        }
        //retrieve the nth last data put into buffer - indexing 
        //starts from 0 (i.e., index = 0 gives last piece of data, 
        //index = 1 gives the second last piece of data)
        T get(int index){
            int loc = (root + index) % size;
            return array[loc];
        }
        void reset(T init){
            root = 0;
            for(int i = 0; i < size; i++){
                array[i] = init;
            }
        }
        
        //average of last n data points
        float runningAvg(int n){
            int sum;
            for(int i = 0; i < n; i++){
                sum += get(n);
            }
            return (float) sum / n; 
        }
    
        //destructor
        ~DataBuffer(){
            delete[] array;
        }
};


#endif