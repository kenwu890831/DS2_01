// 10724128 吳宇哲
// 【工具】–【編譯選項】–【編譯器】勾選【編譯時加入以下命令】
// 加入【-std=c++11】 ，即可運作。

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <new>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std ;

//-------------------------------STACK----------VVVVVVVVVVVVVVVVVVVVVVVV
class StackList;

class StackNode{
private:
    int data; // 存的資料
    StackNode *next; // 指向下一個
public:
    StackNode() {};
    StackNode(int x){
        data = x ; // 添加資料
    }

    friend class StackList;
};

class StackList{
private:
    StackNode *top ;     // remember the address of top element
    int size;           // number of elements in Stack
public:
    StackList():size(0),top(0){};
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int Top();
    int getSize();
    void destroy() ;
};

void StackList::Push(int x){

    if (IsEmpty()) {
        top = new StackNode(x);
        top -> next = NULL ;
        size++;
        return;
    }

    StackNode *newnode = new StackNode(x);  // Push_front() in Linked list
    newnode->next = top;
    top = newnode;
    size++;
}

void StackList::Pop(){

    if (IsEmpty()) {
        //std::cout << "Stack is empty.\n";
        return;
    }

    StackNode *deletenode = top;
    top = top->next;
    delete deletenode;
    deletenode = 0;
    size--;
}

bool StackList::IsEmpty(){
    if ( size == 0 ) {
        top = NULL ;
         return true;
    }
    else
        return false ;
        // if size==0, return true
}

int StackList::Top(){

    if (IsEmpty()) {
        //std::cout << "Stack is empty.\n";
        return  -1;
    }
    return top->data;
}

int StackList::getSize(){

    return size;
}

void StackList::destroy(){
    StackNode *deletenode = top;
    while (!IsEmpty()) {
            deletenode = top ;
            top = top->next;
            delete deletenode;
            deletenode = 0;
            size--;

    }
}
//-------------------------------STACK------------------------------------------------------------------

struct Data {
    int num ; // 序號
    string schoolCode ; // 學校代碼
	string school ; // 學校名稱
	string departmentCode ; // 科系代碼
	string department ; // 科系名稱
	string study ; // 日間/進修別
	string grade ; // 等級別
	string student ; // 學生數
	string teacher ; // 教師數
	string lastyear ; // 上學年畢業生數
	string city ; // 縣市名稱
	string type ; //  體系別
};// 讀取資料用的結構

struct Tree {
    int num ; // 序號
	string student ; // 學生數
	struct Tree *L ;
	struct Tree *R ;
	struct Tree *parent ;

};// 存取資料用的結構


class BuildTree {
	private:
    	int height = 1 ;
    	string inputString ;
    	string title ;
    	vector<struct Data> deap ;
        StackList stack ;
        Tree *maxHeap ;
    	Tree *walk ;
    	Tree *bottom ;
    	Tree *walkParent ;
    	int minDeapCount = 0 ;
    	int maxDeapCount = 0 ;
    	bool minPlace = false, maxPlace = false ;
    public:
		int getNum() {
			int temp ;
			string inputS ;
			bool isNum ;

			do {
				cin >> inputS ;
				isNum = true ;
				for ( int i = 0; ( i < inputS.length()) && ( isNum ) ; i++ )
					if( ( inputS[i] > '9') || ( inputS[i] < '0') ) isNum = false ;
				if ( !isNum ) continue ;
					temp = strtoul( inputS.c_str(), NULL, 10 ) ;

			  	break ;
			} while( true );// end do-while

			return temp ;
		} // getNum()

		bool readTheFileMaxHeap() { // 讀檔
			int tab = 0 ,input = 1, num = 1 ;
			char ch ;
  			cout << endl << "Input a file number (e.g., 101, 102, ...): " ;
  			input = getNum() ; // 讀入檔名
  			inputString = to_string( input ) ; // 將int檔名轉成string
  			fstream theFile;
  			theFile.open( "input"+inputString+".txt" ); // 開啟指定檔案

  			if ( theFile.is_open() ) { // 如果有打開檔案
    			getline( theFile, title ) ;
    			getline( theFile, title ) ;
    			getline( theFile, title ) ; // 讀掉前三行

				while( !theFile.eof() ) {

					struct Data temp;
					temp.num = num ;
					while( theFile.get(ch) && ch!='\n' ) {
                        if( tab == 0 && ch != '\t' ) {
							temp.schoolCode = temp.schoolCode + ch ;
                        }
						else if( tab == 1 && ch != '\t' ) {
							temp.school = temp.school + ch ;
						}
						else if( tab == 2 && ch != '\t' ) {
							temp.departmentCode = temp.departmentCode + ch ;
						}
						else if( tab == 3 && ch != '\t' ) {
							temp.department = temp.department + ch ;
						}
						else if( tab == 4 && ch != '\t' ) {
							temp.study = temp.study + ch ;
						}
						else if( tab == 5 && ch != '\t' ) {
							temp.grade = temp.grade + ch ;
						}
						else if( tab == 6 && ch != '\t' ) {
                            if ( ch >= '0' && ch <= '9')
							temp.student = temp.student + ch ;
						}
						else if( tab == 7 && ch != '\t' ) {
							temp.teacher = temp.teacher + ch ;
						}
						else if( tab == 8 && ch != '\t' ) {
							temp.lastyear = temp.lastyear + ch ;
						}
                        else if( tab == 9 && ch != '\t' ) {
							temp.city = temp.city + ch ;
						}
						else if( tab == 10 && ch != '\t' ) {
							temp.type = temp.type + ch ;
						}

						if( ch=='\t' ) tab++ ;
					} // while
                    num++ ;
                    if ( tab == 10) {
                   //     printdata( temp ) ;
                        createMaxHeap( temp ) ;
                    }

					tab = 0 ;
				} // while

    			theFile.close();
    			return true ;
    		} // if
    		else {
        		cout << "input" +inputString + ".txt does not exist!" << endl ;
        		return false ;
    		} // else
		} // readTheFile task1


		void printdata( Data temp ) {
            cout <<  temp.num << "        "<< temp.schoolCode << "  " << temp.school<< "  " << temp.departmentCode<< "  " << temp.department<< "  " << temp.study<< "   " << temp.grade<< "  " << temp.student<< "   " << temp.teacher<< "  " << temp.lastyear<< "   " << temp.city<< "   " << temp.type << endl ;
		} // print the data

        void createMaxHeap ( Data inputData ) {
            if ( inputData.num == 1 ) {
                maxHeap =new Tree() ;
                maxHeap ->student = inputData.student ;
                maxHeap -> num = inputData.num ;
                maxHeap ->R = NULL ;
                maxHeap ->L = NULL ;
                maxHeap ->parent = NULL ;
                walk = maxHeap ;
            }
            else {
                walk = maxHeap ;
                toBinary( inputData.num ) ;
                while ( !stack.IsEmpty() ) {
                    if ( stack.Top() == 0 ) {
                        if ( walk -> L == NULL ) {
                            Tree *newNode = new Tree() ;
                            newNode -> num = inputData.num ;
                            newNode ->student = inputData.student ;
                            newNode ->parent = walk ;
                            newNode -> L = NULL ;
                            newNode -> R = NULL ;
                            walk -> L = newNode ;
                            walk = newNode ;
                            bottom = newNode ;
                        }
                        else {
                            walk = walk -> L ;
                        }

                        stack.Pop() ;
                    } // if stack top = 0
                    else if (stack.Top() == 1 ) {
                        if ( walk -> R == NULL ) {
                            Tree *newNode = new Tree() ;
                            newNode -> num = inputData.num ;
                            newNode ->student = inputData.student ;
                            newNode ->parent = walk ;
                            newNode -> L = NULL ;
                            newNode -> R = NULL ;
                            walk -> R = newNode ;
                            walk = newNode ;
                            bottom = newNode ;
                        }
                        else {
                            walk = walk -> R ;
                        }
                        stack.Pop() ;
                    } // if stack top = 1
                } // find the bottom if null new a pinter
                maxHeapRebuild() ; // rebuild
            }

        } // createMaxHeap

        void toBinary ( int num ) {
            while ( num != 0 ) {
                int tempNum = num%2 ;
                stack.Push( tempNum ) ;
               // cout << tempNum ;
                num = num / 2 ;

            }
            stack.Pop() ;
            //cout << endl ;

        } // toBinary and pop the first num ( find the bottom )

        void maxHeapRebuild (  ) {
            bool isDone = false ;
            Tree *walkParent = walk -> parent ;
            while ( isDone == false ) {
                int walkStudentNum = stoi (walk -> student ) ;
                int parentStudentNum = stoi (walkParent -> student ) ;
                if ( walkStudentNum<= parentStudentNum) {
                    isDone = true ;
                }
                else if ( walkStudentNum > parentStudentNum){
                    string reBuildTemp = walk -> student ;
                    walk -> student = walkParent -> student ;
                    walkParent -> student = reBuildTemp ;
                    int reBuildTemp2 = walk -> num ;
                    walk -> num = walkParent -> num ;
                    walkParent -> num = reBuildTemp2 ;
                    walk = walk -> parent ;
                    if ( walk != maxHeap)
                        walkParent = walkParent -> parent ;
                    else
                        isDone = true ;
                }
            }

        } // maxHeapRebuild

        void print (  ) {
            cout << "<< Max Heap >> " << endl ;
            cout << endl << "root :  [" << maxHeap -> num << "]  "<< maxHeap ->student << endl ;
            cout << "bottom :  [" << bottom -> num << "]  "<< bottom ->student << endl ;
            walk = maxHeap ;
            while ( walk -> L != NULL) {
                walk = walk -> L ;
            }
            cout << "leftmost bottom :  [" << walk -> num << "]  "<< walk ->student << endl ;
        } // print task 1


        bool readTheFileDeap() { // 讀檔
			int tab = 0 ,input = 1, num = 1 ;
			char ch ;
  			cout << endl << "Input a file number (e.g., 101, 102, ...): " ;
  			input = getNum() ; // 讀入檔名
  			inputString = to_string( input ) ; // 將int檔名轉成string
  			fstream theFile;
  			theFile.open( "input"+inputString+".txt" ); // 開啟指定檔案

  			if ( theFile.is_open() ) { // 如果有打開檔案
    			getline( theFile, title ) ;
    			getline( theFile, title ) ;
    			getline( theFile, title ) ; // 讀掉前三行

				while( !theFile.eof() ) {

					struct Data temp;
					temp.num = num ;
					while( theFile.get(ch) && ch!='\n' ) {
                        if( tab == 0 && ch != '\t' ) {
							temp.schoolCode = temp.schoolCode + ch ;
                        }
						else if( tab == 1 && ch != '\t' ) {
							temp.school = temp.school + ch ;
						}
						else if( tab == 2 && ch != '\t' ) {
							temp.departmentCode = temp.departmentCode + ch ;
						}
						else if( tab == 3 && ch != '\t' ) {
							temp.department = temp.department + ch ;
						}
						else if( tab == 4 && ch != '\t' ) {
							temp.study = temp.study + ch ;
						}
						else if( tab == 5 && ch != '\t' ) {
							temp.grade = temp.grade + ch ;
						}
						else if( tab == 6 && ch != '\t' ) {
                            if ( ch >= '0' && ch <= '9')
							temp.student = temp.student + ch ;
						}
						else if( tab == 7 && ch != '\t' ) {
							temp.teacher = temp.teacher + ch ;
						}
						else if( tab == 8 && ch != '\t' ) {
							temp.lastyear = temp.lastyear + ch ;
						}
                        else if( tab == 9 && ch != '\t' ) {
							temp.city = temp.city + ch ;
						}
						else if( tab == 10 && ch != '\t' ) {
							temp.type = temp.type + ch ;
						}

						if( ch=='\t' ) tab++ ;
					} // while
                    num++ ;
                    if ( tab == 10) {
                       // printdata( temp ) ;
                        createDeap( temp ) ;
                    }

					tab = 0 ;
				} // while

    			theFile.close();
    			return true ;
    		} // if
    		else {
        		cout << "input" +inputString + ".txt does not exist!" << endl ;
        		return false ;
    		} // else
		} // readTheFileDeap

        void createDeap ( Data inputData ) {
            if ( inputData.num == 1 ) {
                Data space ;
                space.student = "  " ;
                space.num = 0 ;
                deap.push_back( space ) ;
                deap.push_back( inputData ) ;
            }
            else  {
                deap.push_back( inputData ) ;
                int place = 0 ; // 相對node
                int level = 0 ; // 層數
                int temp = inputData.num +1 ;
                while ( temp != 0  ) {
                    temp = temp / 2 ;
                    level++ ;
                }
                if ( inputData.num < ((pow(2,level-1) - 1 ) + (pow(2,level-1) / 2 ) )) { // minheap
                    place = ((inputData.num-1)/2)  + (pow(2,level-2) / 2 ) ;
                    if( stoi(deap.at(inputData.num).student) > stoi(deap.at(place).student)) { // 如果小於對應的
                        swapData( inputData.num, place) ;
                        maxDeapRebuild( place ) ;
                    } // if
                    else {
                        minDeapRebuild( inputData.num ) ;
                    }

                }  // minheap end
                else { // max heap
                    place =  inputData.num - (pow(2,level-1) /2 ) ;
                    if( stoi(deap.at(inputData.num).student) < stoi(deap.at(place).student)) { // 如果小於對應的
                        swapData( inputData.num, place) ;
                        minDeapRebuild( place ) ;
                    } // if
                    else {
                        maxDeapRebuild( inputData.num ) ;
                    }
                }//maxheap end
            }
        } // createDeap

        void minDeapRebuild ( int place ) {
            int parent = (place -1 ) /2 ;
            bool isDone = false ;
            while ( !isDone&& parent != 0) {
                if ( stoi(deap.at(place).student) >= stoi(deap.at(parent).student) ) {
                    isDone = true ;
                }
                else {
                    swapData(parent, place) ;
                    place = parent ;
                    parent = (place -1 ) /2 ;
                    if ( parent == 0 )
                        isDone = true ;
                }
            }
        }

        void maxDeapRebuild ( int place ) {
            int parent = (place -1 ) /2 ;
            bool isDone = false ;
            while ( !isDone && parent != 0) {
                if (  stoi(deap.at(place).student) <= stoi(deap.at(parent).student) ) {
                    isDone = true ;
                }
                else {
                    swapData(parent, place) ;
                    place = parent ;
                    parent = (place -1 ) /2 ;
                    if ( parent == 0 )
                        isDone = true ;
                }
            }
        }
        void swapData ( int temp1, int temp2 ) {
            string sTemp = deap.at(temp1).student ;
            deap.at(temp1).student =deap.at(temp2).student ;
            deap.at(temp2).student = sTemp ;
            int nTemp = deap.at(temp1).num ;
            deap.at(temp1).num = deap.at(temp2).num ;
            deap.at(temp2).num = nTemp ;
        }

        void printDeap (  ) {
            cout << "<< DEAP >> " << endl ;
            int size = deap.size() ;
            cout << "bottom :  [" << deap.at(size-1).num << "]  "<< deap.at(size-1).student << endl ;
            int level =0;
            while ( size != 0  ) {
                    size = size / 2 ;
                    level++ ;
            }
            int leftnode = pow(2,level-1) -1 ;
            cout << "leftmost bottom :  [" << deap.at(leftnode).num << "]  "<< deap.at(leftnode).student << endl ;
            deap.clear() ;
        } // print
        
        bool readTheFileMinMaxHeap() { // 讀檔
			int tab = 0 ,input = 1, num = 1 ;
			char ch ;
  			cout << endl << "Input a file number (e.g., 101, 102, ...): " ;
  			input = getNum() ; // 讀入檔名
  			inputString = to_string( input ) ; // 將int檔名轉成string
  			fstream theFile;
  			theFile.open( "input"+inputString+".txt" ); // 開啟指定檔案

  			if ( theFile.is_open() ) { // 如果有打開檔案
    			getline( theFile, title ) ;
    			getline( theFile, title ) ;
    			getline( theFile, title ) ; // 讀掉前三行

				while( !theFile.eof() ) {

					struct Data temp;
					temp.num = num ;
					while( theFile.get(ch) && ch!='\n' ) {
                        if( tab == 0 && ch != '\t' ) {
							temp.schoolCode = temp.schoolCode + ch ;
                        }
						else if( tab == 1 && ch != '\t' ) {
							temp.school = temp.school + ch ;
						}
						else if( tab == 2 && ch != '\t' ) {
							temp.departmentCode = temp.departmentCode + ch ;
						}
						else if( tab == 3 && ch != '\t' ) {
							temp.department = temp.department + ch ;
						}
						else if( tab == 4 && ch != '\t' ) {
							temp.study = temp.study + ch ;
						}
						else if( tab == 5 && ch != '\t' ) {
							temp.grade = temp.grade + ch ;
						}
						else if( tab == 6 && ch != '\t' ) {
                            if ( ch >= '0' && ch <= '9')
							temp.student = temp.student + ch ;
						}
						else if( tab == 7 && ch != '\t' ) {
							temp.teacher = temp.teacher + ch ;
						}
						else if( tab == 8 && ch != '\t' ) {
							temp.lastyear = temp.lastyear + ch ;
						}
                        else if( tab == 9 && ch != '\t' ) {
							temp.city = temp.city + ch ;
						}
						else if( tab == 10 && ch != '\t' ) {
							temp.type = temp.type + ch ;
						}

						if( ch=='\t' ) tab++ ;
					} // while
                    num++ ;
                    if ( tab == 10) {
                       // printdata( temp ) ;
                        createMinMaxHeap( temp ) ;
                    }

					tab = 0 ;
				} // while

    			theFile.close();
    			return true ;
    		} // if
    		else {
        		cout << "input" +inputString + ".txt does not exist!" << endl ;
        		return false ;
    		} // else
		} // readTheFileminmaxheap
		
		
		void createMinMaxHeap ( Data inputData ) {
            if ( inputData.num == 1 ) {
                deap.push_back( inputData ) ;
            }
            else  {
                deap.push_back( inputData ) ;
                int parent = 0 ; // 相對node
                parent = ( inputData.num / 2 ) -1 ;
                int level = 0 ; // 層數
                int temp = inputData.num ;
                while ( temp != 0  ) {
                    temp = temp / 2 ;
                    level++ ;
                }
                if ( level % 2 == 1 ) {//min
                	if ( stoi(deap.at(inputData.num-1).student) > stoi(deap.at(parent).student)) {
                		swapData( inputData.num-1, parent) ;
                		minMaxHeapRebuildmax( parent ) ;
					}
					else {
						minMaxHeapRebuildmin( inputData.num-1 ) ;
					}
				}
				else {//max
					if ( stoi(deap.at(inputData.num-1).student) < stoi(deap.at(parent).student)) {
                		swapData( inputData.num-1, parent) ;
                		minMaxHeapRebuildmin( parent ) ;
					}
					else {
						minMaxHeapRebuildmax( inputData.num-1 ) ;
					}
				}
                //if ( stoi(deap.at(place).student) >= stoi(deap.at(parent).student))
                
            }
        } // createMinMaxHeap
        
        
        void minMaxHeapRebuildmax ( int place ) {
            int parent = (place -1 ) /2 ;
            parent = (parent -1 ) /2 ;
            bool isDone = false ;
            while ( !isDone && parent != 0) {
                if (  stoi(deap.at(place).student) <= stoi(deap.at(parent).student) ) {
                    isDone = true ;
                }
                else {
                    swapData(parent, place) ;
                    place = parent ;
                    parent = (place -1 ) /2 ;
                    parent = (parent -1 ) /2 ;
                    if ( parent == 0 )
                        isDone = true ;
                }
            }
        }
        
        void minMaxHeapRebuildmin ( int place ) {
            int parent = (place -1 ) /2 ;
            parent = (parent -1 ) /2 ;
            bool isDone = false ;
            while ( !isDone ) {
                if (  stoi(deap.at(place).student) >= stoi(deap.at(parent).student) ) {
                    isDone = true ;
                }
                else {
                    swapData(parent, place) ;
                    place = parent ;
                    parent = (place -1 ) /2 ;
                    parent = (parent -1 ) /2 ;
                }
            }
        }
        
        void printMinMaxHeap (  ) {
            cout << "<< Min-Max HEAP >> " << endl ;
            cout << "root :  [" << deap.at(0).num << "]  "<< deap.at(0).student << endl ;
            int size = deap.size() ;
            cout << "bottom :  [" << deap.at(size-1).num << "]  "<< deap.at(size-1).student << endl ;
            int level =0;
            while ( size != 0  ) {
                    size = size / 2 ;
                    level++ ;
            }
            int leftnode = pow(2,level-1) -1 ;
            cout << "leftmost bottom :  [" << deap.at(leftnode).num << "]  "<< deap.at(leftnode).student << endl ;
            deap.clear() ;
        } // printMinMaxHeap



};

int main(){
    BuildTree t ;
    bool check = false ;
   	int command = 0 ; // user command
  	do {

  		cout << endl << "**** Heap Construction *****" ;
  		cout << endl << "* 0. QUIT                  *" ;
  		cout << endl << "* 1. Build a max heap      *" ;
  		cout << endl << "* 2. Build a DEAP          *" ;
  		cout << endl << "* 3. Build a min-max heap  *" ;
  		cout << endl << "*************************************" ;
  		cout << endl << "Input a command( 0, 1, 2, 3 ) : " ;
  		cin >> command ; // get the command
  		switch(command){
			case 0 : break ; //跳出，結束

  			case 1 : //
        		check = t.readTheFileMaxHeap() ; // 讀檔
        		if ( check )
                    t.print() ;
         	   	break ;
  			case 2 : //
  			    check = t.readTheFileDeap() ;
  			    if ( check )
                    t.printDeap() ;
  				break ;
  				
  			case 3 : //
  			    check = t.readTheFileMinMaxHeap() ;
  			    if ( check )
                    t.printMinMaxHeap() ;
  				break ;

  			default :
				cout << endl << "command does not exist !!" << endl ;
  				break ;

		} // end switch

  	} while ( command != 0 ) ;

	system( "pause") ; // pause the display
  	return 0 ;
}
