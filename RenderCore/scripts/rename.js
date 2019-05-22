var fs = require("fs")
var path = require("path")

var root = path.resolve('/Users/furture/code/weex-render/RenderCore/render');

transformDir(root);

function transformDir(file){
     var pa = fs.readdirSync(file);
     pa.forEach(function(ele, index){
         var info  = fs.statSync(file + "/" + ele);
         if(info.isDirectory()){
            transformDir(file+"/"+ele);
         }else{
           transformFile(file+"/"+ele);
         }
     });
}

function transformFile(file){
  if(file.endsWith(".so") || file.endsWith(".o") || file.endsWith(".a") || file.endsWith(".idx")
    || file.endsWith(".pack")){
    return;
  }
  var content = fs.readFileSync(file, 'utf8');
  //content = content.replace(/weexrender/g, "weexuikit");
  //content = content.replace(/RENDERANDROID/g, "WEEX_UIKIT");
  content = content.replace(/WEEX_UIKITER/g, "WEEX_UIKIT");
  
  
  fs.writeFileSync(file, content);
  //console.log(content);
  console.log(file);
}
