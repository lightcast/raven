
class Stack{
    constructor(size){
        this.size = size;
        this.stack = new Array();
      }
    
      push(item){
        if(this.stack.length < this.size){
          this.stack.push(item);
        }
      }
    
      pop(){
        let result = -1;
        if(this.stack.length != 0){
          result = this.stack.pop();
        }
        return result;
      }
    
      display(){
        if(this.stack == undefined || this.stack.length === 0){
          console.log("Stack is empty!");
        }else{
          console.log("Stack data:");
          let arry = this.stack.reverse();
          for(let item in arry){
            item = arry[item]
          }
        }
      }
    
      isEmpty(){
        return this.stack.length === 0
      }
    
      topChar(){
        let result = -1;
    
        if(this.stack.length !== 0){
          result = this.stack[this.stack.length - 1];
        }
        return result;
      }
    
    }
    
    const operators = "+-*/^";
    
    function isOperator(char){
      return operators.includes(char);
    }
    
    function isOperand(char){
      if(typeof Number(char) === 'number'){
        return Number(char) >= 0 && Number(char) <= 9 
      }
      return false;
    }
    
    function getPrecedence(c){
      let result = 0;
      let str = '-/';
      for(let char in operators){
        char = operators[char];
    
        result += 1;
    
        if(char == c){
          if(str.includes(c)){
            result -=1;
          }
          break;
        }
      }
      return result;
    }
    
    function toPostFix(expression){
      let result = "";
      let stack = new Stack(15);
      let cpop;
    
      for(let char in expression){
        char = expression[char];
        if(isOperand(char)){
    
          result += char;
        } else if(isOperator(char)){
          while (true){
            topChar = stack.topChar();
            if(stack.isEmpty() || topChar === '('){
    
              stack.push(char);
              break;
            }else{
              let pC = getPrecedence(char);
              let pTC = getPrecedence(topChar);
    
              if(pC > pTC){
                stack.push(char);
                break;
              }else{
               // stack.display();
                result += stack.pop();
              } 
            } 
          }
        } else if(char == '('){
          stack.push(char);
        } else if(char == ')'){
          cpop = stack.pop();
    
          while(cpop != '('){
            result += cpop;
            cpop = stack.pop();
          } 
        }
      }
    
      while(!stack.isEmpty()){
        cpop = stack.pop();
        result += cpop;
      }
      return result;
    }
    /*
    let arr = infixExps = [
        'A*B+C',    // AB*C+
        'A+B*C',   // ABC*+ 
        'A*B+C*D',  // AB*CD*+
        'A*B^C+D',  // ABC^*D+ 
        'A*(B+C*D)+E',          // ABCD*+*E+  
        'A+(B*C-(D/E^F)*G)*H',  // ABC*DEF^/G*-H*+
        '(A+B)*C+D/(E+F*G)-H',  // AB+C*DEFG*+/+H-
        'A-B-C*(D+E/F-G)-H'     // AB-CDEF/+G-*-H-
    ]; */
    
    
    let arr = infixExps = [
      '1*2+3', //12*3+
      '1+2*3', //123*+
      '1*2+3*4', //12*34*+
      '1*(2+3*4)+5', //1234*+*5+
       '(1+2)*3+4/(5+6*7)-8', //12+3*4567*+/+8-
    
       '1-2-3*(4+5/6-7)-8' //12-3456/+7-*-8-
    ];
    
    
    // '
    
    /*
     
        '1*2^3+4',  // 123^*4+ 
        
        '1+(2*3-(4/5^6)*7)*8', //123*456^/7*-8*+
       
        
    */
    
    
    
    /*
    for(exp in infixExps){
      exp = infixExps[exp];
      let  postfix = toPostFix(exp)
      console.log(`Infix: ${exp} -> Postfix: ${postfix}`);
    }
    
    */
    
    
    /*
    
    let arry = ['a', 'b', 'c'];
        
        for (var i in arry.reverse()) {
          console.log(arry[i]);
        } */
    
    
    function shuntingYard(expression){
        let stack = new Stack(15);
        let result;
      for(let char in expression){
        char = expression[char];
        let rightOperand;
        let leftOperand;
        
    
        if(isOperand(char)){
          stack.push(char);
        }else if(isOperator(char)){
          if(!stack.isEmpty()){
            rightOperand = stack.pop();
          }
          
          if(!stack.isEmpty()){
            leftOperand = stack.pop();
          }
    
          if(rightOperand && leftOperand){
            switch(char){
              case '+':
                result = Number(leftOperand) + Number(rightOperand);
                break;
              case '*':
                result = Number(leftOperand) * Number(rightOperand);
                break;
              case '-':
                result = Number(leftOperand) - Number(rightOperand);
                break;
              case '/':
                result = Number(leftOperand) / Number(rightOperand);
                break;
            }
    
            if(result){
              stack.push(result);
            }
          }
        }
      }
      return result;
    }
    
    
    console.log(shuntingYard('12*3+'));
    console.log(shuntingYard('123*+'));
    console.log(shuntingYard('12*34*+'));
    console.log(shuntingYard('1234*+*5+'));
    console.log(shuntingYard('12+3*4567*+/+8-'));
    console.log(shuntingYard('12-3456/+7-*-8-'));
    
    
    
    