#ifndef BINTREE_H
#define BINTREE_H

#include <list>
#include <queue>
#include <stack>

#include <cmath> ///abs

template <class valueType>
class treeElement{
    valueType value;

    treeElement *right, *left;
public:
    treeElement(){
        this->right = 0;
        this->left = 0;
    }

    treeElement(valueType value){
        this->right = 0;
        this->left = 0;
        this->value = value;
    }

    treeElement(treeElement *value){
        this->right = value->right;
        this->left = value->left;
        this->value = value->value;
    }

    ~treeElement(){
        if (this){
            delete left;
            delete right;
        }
        //delete
        //at least try to
    }

    valueType getValue(){
        return value;
    }

    treeElement* getLeft(){
        return left;
    }

    treeElement* getRight(){
        return right;
    }

    int amountOfElements(){
        if (this == 0){
            return 0;
        }else{
            return 1 + getLeft()->amountOfElements() + getRight()->amountOfElements();
        }
    }

    bool setValue(valueType n){
        value = n;
        return true;
    }

    bool setValue(treeElement *n){
        value = n->value;
        return true;
    }

    bool setLeft(treeElement *n){
        left = n;
        return true;
    }

    bool setRight(treeElement *n){
        right = n;
        return true;
    }

    bool setLeft(valueType value, bool force = false){
        treeElement *tmp = new treeElement(value);

        if (force){
            delete left;
            left = tmp;
            return true;
        }else{
            if (left == 0){
                left = tmp;
                return true;
            }else{
                return false;
            }
        }
    }

    bool setRight(valueType value, bool force = false){
        treeElement *tmp = new treeElement(value);

        if (force){
            delete right;
            right = tmp;
            return true;
        }else{
            if (right == 0){
                right = tmp;
                return true;
            }else{
                return false;
            }
        }
    }

    std::list<valueType> levelOrder(treeElement* (treeElement::*first)(),treeElement* (treeElement::*second)()){
        std::list<valueType> result;

        if (this != 0){
            std::queue<treeElement *>  que;
            que.push(this);

            while (!que.empty()){
                treeElement* tmp = que.front();
                que.pop();

                result.push_back(tmp->getValue());

                if ((tmp->*first)() != 0){
                    que.push((tmp->*first)());
                }

                if ((tmp->*second)() != 0){
                    que.push((tmp->*second)());
                }
            }
        }
        return result;

    }

    std::list<valueType> preOrder(treeElement* (treeElement::*first)(),treeElement* (treeElement::*second)()){
        std::list<valueType> result;

        if (this != 0){
            result.push_back(this->getValue());
            std::list<int> tmp = (this->*first)()->preOrder(first, second);

            while (!tmp.empty()){
                result.push_back(tmp.front());
                tmp.pop_front();
            }

            tmp = (this->*second)()->preOrder(first, second);
            while (!tmp.empty()){
                result.push_back(tmp.front());
                tmp.pop_front();
            }
        }

        return result;
    }

    std::list<valueType> inOrder(treeElement* (treeElement::*first)(),treeElement* (treeElement::*second)()){
        std::list<valueType> result;

        if (this != 0){

            std::list<int> tmp = (this->*first)()->inOrder(first, second);
            while (!tmp.empty()){
                result.push_back(tmp.front());
                tmp.pop_front();
            }

            result.push_back(this->getValue());

            tmp = (this->*second)()->inOrder(first, second);
            while (!tmp.empty()){
                result.push_back(tmp.front());
                tmp.pop_front();
            }
        }

        return result;
    }

    std::list<valueType> postOrder(treeElement* (treeElement::*first)(),treeElement* (treeElement::*second)()){
        std::list<valueType> result;

        if (this != 0){

            std::list<int> tmp = (this->*first)()->postOrder(first, second);
            while (!tmp.empty()){
                result.push_back(tmp.front());
                tmp.pop_front();
            }

            tmp = (this->*second)()->postOrder(first, second);
            while (!tmp.empty()){
                result.push_back(tmp.front());
                tmp.pop_front();
            }

            result.push_back(this->getValue());

        }

        return result;
    }

    std::list<valueType> iterativeOrder(treeElement* (treeElement::*first)(),treeElement* (treeElement::*second)()){
        std::list<valueType> result;

        if (this != 0){
            std::stack<treeElement*> stack;
            stack.push(this);

            while (!stack.empty()){
                treeElement *temp = stack.top();
                stack.pop();

                result.push_back(temp->getValue());

                if ((temp->*first)()){
                    stack.push((temp->*first)());
                }
                if ((temp->*second)()){
                    stack.push((temp->*second)());
                }
            }
        }

        return result;
    }
};

template <class valueType>
class BinTree
{
    treeElement<valueType> *root;
public:
    BinTree(){
        root = 0;
    }

    void addValue(valueType value){
        if (root == 0){
            root = new treeElement<valueType>(value);
        }else{
            treeElement<valueType> *tmp = root;

            treeElement<valueType> *prev = 0;
            while (tmp != 0){
                prev = tmp;
                if (tmp->getValue() > value){
                    tmp = tmp->getRight();
                }else{
                    tmp = tmp->getLeft();
                }
                //What about tmp->getValue() == value? IDK.
            }

            if (prev->getValue() > value){
                prev->setRight(value);
            }else{
                prev->setLeft(value);
            }
        }
    }
    /// Can try equal = valueType::operator== :D
    void delValue(valueType value){
        treeElement<valueType> *tmp = root;
        treeElement<valueType> *prev;
        //SEARCH
        while (tmp && !(value== tmp->getValue())){
            prev = tmp;
            if (tmp->getValue() > value){
                tmp = tmp->getRight();
            }else{
                tmp = tmp->getLeft();
            }
        }

        if (tmp){
            if (!tmp->getLeft()){
                prev->setRight(tmp->getRight());
                //free tmp
            }else if (!tmp->getRight()){
                prev->setLeft(tmp->getLeft());
                //free tmp
            }else{
                treeElement<valueType> *prevmin = tmp;
                treeElement<valueType> *min = tmp->getRight();
                while (min->getLeft()){
                    prevmin = min;
                    min = min->getLeft();
                }
                tmp->setValue(min);
                if (prevmin->getLeft() == min){
                    prevmin->setLeft(nullptr);
                }else if (prevmin->getRight() == min){
                    prevmin->setRight(nullptr);
                }
            }
        }else{
            return;
        }
    }

    void addValue(std::list<valueType> values){
        while (!values.empty()){
            this->addValue(values.front());
            values.pop_front();
        }
    }

    void delValue(std::list<valueType> values){
        while (!values.empty()){
            this->delValue(values.front());
            values.pop_front();
        }
    }

    treeElement<valueType> *findValue(valueType value){
        return findValue(new treeElement<valueType>(value));
    }

    treeElement<valueType> *findValue(treeElement<valueType> *value){
        treeElement<valueType> *tmp = root;
        //SEARCH
        while (tmp && !(value->getValue() == tmp->getValue())){
            if (tmp->getValue()> value->getValue()){
                tmp = tmp->getRight();
            }else{
                tmp = tmp->getLeft();
            }
        }
        return tmp;
    }

    bool isBalanced(){
        return isBalanced(root);
    }

    bool isBalanced(treeElement<valueType> *current){
        if (current != 0){
            bool diferance = std::abs(current->getRight()->amountOfElements() - current->getLeft()->amountOfElements()) < 2;
            if (diferance){
                return isBalanced(current->getRight()) && isBalanced(current->getLeft());
            }else{
                return false;
            }
        }else{
            return true;
        }
    }

    std::list<valueType> levelOrder(treeElement<valueType>* (treeElement<valueType>::*first)(),treeElement<valueType>* (treeElement<valueType>::*second)()){
        return root->levelOrder(first, second);

    }

    std::list<valueType> preOrder(treeElement<valueType>* (treeElement<valueType>::*first)(),treeElement<valueType>* (treeElement<valueType>::*second)()){
        return root->preOrder(first, second);
    }

    std::list<valueType> inOrder(treeElement<valueType>* (treeElement<valueType>::*first)(),treeElement<valueType>* (treeElement<valueType>::*second)()){
        return root->inOrder(first, second);
    }

    std::list<valueType> postOrder(treeElement<valueType>* (treeElement<valueType>::*first)(),treeElement<valueType>* (treeElement<valueType>::*second)()){
        return root->postOrder(first, second);
    }


};

#endif // BINTREE_H
