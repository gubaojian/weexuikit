//
// Created by furture on 2019/2/18.
//

#include <render/platform/transforms/TransformOperations.h>
#include <render/platform/transforms/RotateTransformOperation.h>
#include <render/platform/transforms/TranslateTransformOperation.h>
#include <render/platform/transforms/ScaleTransformOperation.h>
#include <render/platform/transforms/PerspectiveTransformOperation.h>
#include <render/platform/transforms/SkewTransformOperation.h>
#include <render/platform/transforms/Matrix3DTransformOperation.h>
#include <render/platform/transforms/MatrixTransformOperation.h>
#include <render/core/parser/StyleParser.h>
#include <map>
#include <render/platform/common/log.h>
#include "TransformParser.h"


namespace weexuikit{

    namespace TransformParser {

        /**
         * https://developer.mozilla.org/en-US/docs/Web/CSS/transform-function/rotate
         * */
        static PassRefPtr<blink::TransformOperation> parseTransformRotate(std::string& function, blink::TransformOperation::OperationType operationType){
            std::vector<std::string>  tokens = StyleParser::parseFunctionArgs(function);
            if(operationType == blink::TransformOperation::OperationType::Rotate3D){
                double x = 0;
                double y = 0;
                double z = 0;
                double deg = 0;
                if(tokens.size() == 4){
                    x = StyleParser::parseStringToDeg(tokens.at(0));
                    y = StyleParser::parseStringToDeg(tokens.at(0));
                    z = StyleParser::parseStringToDeg(tokens.at(0));
                    deg = StyleParser::parseStringToDeg(tokens.at(0));
                }
                return blink::RotateTransformOperation::create(x, y, z, deg, blink::TransformOperation::OperationType::Rotate3D);

            }else if(operationType == blink::TransformOperation::OperationType::RotateX){
                double deg = 0;
                if(tokens.size() == 1){
                    deg = StyleParser::parseStringToDeg(tokens.at(0));
                }
                return blink::RotateTransformOperation::create(1, 0, 0, deg, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::RotateY){
                double deg = 0;
                if(tokens.size() == 1){
                    deg = StyleParser::parseStringToDeg(tokens.at(0));
                }
                return blink::RotateTransformOperation::create(0, 1, 0, deg, operationType);
            }else{
                double deg = 0;
                if(tokens.size() == 1){
                    deg = StyleParser::parseStringToDeg(tokens.at(0));
                }
                return blink::RotateTransformOperation::create(deg, operationType);
            }
        }


        /**
         * https://developer.mozilla.org/en-US/docs/Web/CSS/transform-function/skew
         * */
        static PassRefPtr<blink::TransformOperation> parseTransformSkew(std::string& function, blink::TransformOperation::OperationType operationType) {
            std::vector<std::string>  argsTokens = StyleParser::parseFunctionArgs(function);
            if(operationType ==  blink::TransformOperation::OperationType::Skew){
                double angleX = 0;
                double angleY = 0;
                if(argsTokens.size() == 1){
                    angleX = StyleParser::parseStringToDeg(argsTokens.at(0));
                    angleY = angleX;
                }else if(argsTokens.size() == 2){
                    angleX = StyleParser::parseStringToDeg(argsTokens.at(0));
                    angleY = StyleParser::parseStringToDeg(argsTokens.at(1));
                }
                return blink::SkewTransformOperation::create(angleX, angleY, blink::TransformOperation::OperationType::Skew);
            }else if(operationType ==  blink::TransformOperation::OperationType::SkewX){
                double angleX = 0;
                if(argsTokens.size() == 1){
                    angleX = StyleParser::parseStringToDeg(argsTokens.at(0));
                }
                return blink::SkewTransformOperation::create(angleX, 0, blink::TransformOperation::OperationType::SkewX);

            }else if(operationType ==  blink::TransformOperation::OperationType::SkewY){
                double angleY = 0;
                if(argsTokens.size() == 1){
                    angleY = StyleParser::parseStringToDeg(argsTokens.at(0));
                }
                return blink::SkewTransformOperation::create(0, angleY, blink::TransformOperation::OperationType::SkewY);
            }
            return blink::SkewTransformOperation::create(0, 0, blink::TransformOperation::OperationType::Skew);
        }

        /**
         * https://developer.mozilla.org/en-US/docs/Web/CSS/transform-function/matrix
         * */
        static PassRefPtr<blink::TransformOperation> parseTransformMatrix(std::string& function) {
            double a = 0;
            double b = 0;
            double c = 0;
            double d = 0;
            double e = 0;
            double f = 0;
            std::vector<std::string>  argsTokens = StyleParser::parseFunctionArgs(function);
            if(argsTokens.size() == 6){
                a = StyleParser::parseStringToDouble(argsTokens.at(0));
                b = StyleParser::parseStringToDouble(argsTokens.at(1));
                c = StyleParser::parseStringToDouble(argsTokens.at(2));
                d = StyleParser::parseStringToDouble(argsTokens.at(3));
                e = StyleParser::parseStringToDouble(argsTokens.at(4));
                f = StyleParser::parseStringToDouble(argsTokens.at(5));
            }
            return blink::MatrixTransformOperation::create(a, b, c, d, e, f);
        }

        /**
        * https://developer.mozilla.org/en-US/docs/Web/CSS/transform-function/matrix3d
        * */
        static PassRefPtr<blink::TransformOperation> parseTransformMatrix3D(std::string& function) {
            double m11 = 0;
            double m12 = 0;
            double m13 = 0;
            double m14 = 0;
            double m21 = 0;
            double m22 = 0;
            double m23 = 0;
            double m24 = 0;
            double m31 = 0;
            double m32 = 0;
            double m33 = 0;
            double m34 = 0;
            double m41 = 0;
            double m42 = 0;
            double m43 = 0;
            double m44 = 0;
            std::vector<std::string>  argsTokens = StyleParser::parseFunctionArgs(function);
            if(argsTokens.size() == 16){
                m11 = StyleParser::parseStringToDouble(argsTokens.at(0));
                m12 = StyleParser::parseStringToDouble(argsTokens.at(1));
                m13 = StyleParser::parseStringToDouble(argsTokens.at(2));
                m14 = StyleParser::parseStringToDouble(argsTokens.at(3));
                m21 = StyleParser::parseStringToDouble(argsTokens.at(4));
                m22 = StyleParser::parseStringToDouble(argsTokens.at(5));
                m23 = StyleParser::parseStringToDouble(argsTokens.at(6));
                m24 = StyleParser::parseStringToDouble(argsTokens.at(7));
                m31 = StyleParser::parseStringToDouble(argsTokens.at(8));
                m32 = StyleParser::parseStringToDouble(argsTokens.at(9));
                m33 = StyleParser::parseStringToDouble(argsTokens.at(10));
                m34 = StyleParser::parseStringToDouble(argsTokens.at(11));
                m41 = StyleParser::parseStringToDouble(argsTokens.at(12));
                m42 = StyleParser::parseStringToDouble(argsTokens.at(13));
                m43 = StyleParser::parseStringToDouble(argsTokens.at(14));
                m44 = StyleParser::parseStringToDouble(argsTokens.at(15));
            }
            blink::TransformationMatrix matrix(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
            return blink::Matrix3DTransformOperation::create(matrix);
        }
        /**
         * https://developer.mozilla.org/en-US/docs/Web/CSS/transform-function/translate
         * */
        static PassRefPtr<blink::TransformOperation> parseTransformTranslate(std::string& function, blink::TransformOperation::OperationType operationType){
            std::vector<std::string>  tokens = StyleParser::parseFunctionArgs(function);
            blink::Length x = {0, blink::LengthType::Fixed};
            blink::Length y = {0, blink::LengthType::Fixed};
            if(operationType == blink::TransformOperation::OperationType::Translate){
                if(tokens.size() == 2){
                    x = StyleParser::parseStringToLengthUnit(tokens.at(0));
                    y = StyleParser::parseStringToLengthUnit(tokens.at(1));
                }
                return blink::TranslateTransformOperation::create(x, y, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::TranslateX){
                if(tokens.size() == 1){
                    x = StyleParser::parseStringToLengthUnit(tokens.at(0));
                }
                return blink::TranslateTransformOperation::create(x, y, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::TranslateY){
                 if(tokens.size() == 1){
                    y = StyleParser::parseStringToLengthUnit(tokens.at(0));
                }
                return blink::TranslateTransformOperation::create(x, y, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::TranslateZ){
                double z = 0;
                if(tokens.size() == 1){
                    StyleParser::parseStringByViewPortUnit(tokens.at(0));
                }
                return blink::TranslateTransformOperation::create(x, y, z, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::Translate3D){
                double z = 0;
                if(tokens.size() == 3){
                    x = StyleParser::parseStringToLengthUnit(tokens.at(0));
                    y = StyleParser::parseStringToLengthUnit(tokens.at(1));
                    z = StyleParser::parseStringByViewPortUnit(tokens.at(2));
                }
                return blink::TranslateTransformOperation::create(x, y, z, operationType);
            }
            return blink::TranslateTransformOperation::create(x, y, operationType);
        }



        /**
         * https://developer.mozilla.org/en-US/docs/Web/CSS/transform-function/scale
         * */
        static PassRefPtr<blink::TransformOperation> parseTransformScale(std::string& function, blink::TransformOperation::OperationType operationType){
            std::vector<std::string>  tokens = StyleParser::parseFunctionArgs(function);
            if(operationType == blink::TransformOperation::OperationType::Scale){
                double x, y;
                if(tokens.size() == 2){
                    x = StyleParser::parseStringToDouble(tokens.at(0));
                    y = StyleParser::parseStringToDouble(tokens.at(1));
                }
                return blink::ScaleTransformOperation::create(x, y, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::ScaleX){
                double x;
                if(tokens.size() == 1){
                    x = StyleParser::parseStringToDouble(tokens.at(0));
                }
                return blink::ScaleTransformOperation::create(x, 0, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::ScaleY){
                double y;
                if(tokens.size() == 1){
                    y = StyleParser::parseStringToDouble(tokens.at(0));
                }
                return blink::ScaleTransformOperation::create(0, y, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::ScaleZ){
                double z;
                if(tokens.size() == 1){
                    z = StyleParser::parseStringToDouble(tokens.at(0));
                }
                return blink::ScaleTransformOperation::create(0, 0, z, operationType);
            }else if(operationType == blink::TransformOperation::OperationType::Scale3D){
                double x, y, z;
                if(tokens.size() == 3){
                    x = StyleParser::parseStringToDouble(tokens.at(0));
                    y = StyleParser::parseStringToDouble(tokens.at(1));
                    z = StyleParser::parseStringToDouble(tokens.at(2));
                }
                return blink::ScaleTransformOperation::create(x, y, z, operationType);
            }
            return blink::ScaleTransformOperation::create(0, 0, operationType);
        }


        static PassRefPtr<blink::TransformOperation> parseTransformPerspective(std::string& function){
            std::vector<std::string>  tokens = StyleParser::parseFunctionArgs(function);
            double perspective = 0;
            if(tokens.size() == 1){
                perspective = StyleParser::parseStringToDouble(tokens.at(0));
            }
            return blink::PerspectiveTransformOperation::create(perspective);
        }


        static std::vector<std::string> parseTransformFunctions(const std::string transform){
            std::vector<std::string> functions;
            int start = 0;
            while(start < transform.length()){
                std::size_t left = transform.find("(", start);
                std::size_t right = transform.find(")", start);
                if(left != std::string::npos
                   && right != std::string::npos){
                    std::string function = transform.substr(start, right - start + 1);
                    StyleParser::trimStringSpace(function);
                    functions.push_back(function);
                    start = right + 1;
                    continue;
                }
                break;
            }
            return functions;
        }

        blink::TransformOperations parseTransform(const std::string& transform){

            blink::TransformOperations transformOperations;
            std::vector<std::string> functions = parseTransformFunctions(transform);
            for(std::string& function : functions){
                std::string functionName = StyleParser::parseFunctionName(function);
                if(functionName == Html::Style::STYLE_TRANSFORM_ROTATE){
                    transformOperations.operations().append(parseTransformRotate(function, blink::TransformOperation::OperationType::Rotate));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_ROTATE_X){
                    transformOperations.operations().append(parseTransformRotate(function, blink::TransformOperation::OperationType::RotateX));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_ROTATE_Y){
                    transformOperations.operations().append(parseTransformRotate(function, blink::TransformOperation::OperationType::RotateY));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_ROTATE_Z){
                    transformOperations.operations().append(parseTransformRotate(function, blink::TransformOperation::OperationType::RotateZ));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_ROTATE_3D){
                    transformOperations.operations().append(parseTransformRotate(function, blink::TransformOperation::OperationType::Rotate3D));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_TRANSLATE){
                    transformOperations.operations().append(parseTransformTranslate(function, blink::TransformOperation::OperationType::Translate));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_TRANSLATE_X){
                    transformOperations.operations().append(parseTransformTranslate(function, blink::TransformOperation::OperationType::TranslateX));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_TRANSLATE_Y){
                    transformOperations.operations().append(parseTransformTranslate(function, blink::TransformOperation::OperationType::TranslateY));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_TRANSLATE_Z){
                    transformOperations.operations().append(parseTransformTranslate(function, blink::TransformOperation::OperationType::TranslateZ));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_TRANSLATE_3D){
                    transformOperations.operations().append(parseTransformTranslate(function, blink::TransformOperation::OperationType::Translate3D));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SCALE){
                    transformOperations.operations().append(parseTransformScale(function, blink::TransformOperation::OperationType::Scale));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SCALE_X){
                    transformOperations.operations().append(parseTransformScale(function, blink::TransformOperation::OperationType::ScaleX));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SCALE_Y){
                    transformOperations.operations().append(parseTransformScale(function, blink::TransformOperation::OperationType::ScaleY));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SCALE_Z){
                    transformOperations.operations().append(parseTransformScale(function, blink::TransformOperation::OperationType::ScaleZ));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SCALE_3D){
                    transformOperations.operations().append(parseTransformScale(function, blink::TransformOperation::OperationType::Scale3D));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_PERSPECTIVE){
                    transformOperations.operations().append(parseTransformPerspective(function));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SKEW){
                    transformOperations.operations().append(parseTransformSkew(function, blink::TransformOperation::OperationType::Skew));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SKEW_X){
                    transformOperations.operations().append(parseTransformSkew(function, blink::TransformOperation::OperationType::SkewX));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_SKEW_Y){
                    transformOperations.operations().append(parseTransformSkew(function, blink::TransformOperation::OperationType::SkewY));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_MATRIX){
                    transformOperations.operations().append(parseTransformMatrix(function));
                }else if(functionName == Html::Style::STYLE_TRANSFORM_MATRIX_3D){
                    transformOperations.operations().append(parseTransformMatrix3D(function));
                }
            }
            return transformOperations;
        }



        static blink::Length parseTransformOriginToLength(std::string &transformOrigin, bool &isXOrigin) {
            if(transformOrigin == Html::Style::STYLE_TRANSFORM_ORIGIN_LEFT){
                return blink::Length(0, blink::LengthType::Percent);
            }else if(transformOrigin == Html::Style::STYLE_TRANSFORM_ORIGIN_RIGHT){
                return blink::Length(100, blink::LengthType::Percent);
            }else if(transformOrigin == Html::Style::STYLE_TRANSFORM_ORIGIN_CENTER){
                return blink::Length(50, blink::LengthType::Percent);
            }else if(transformOrigin == Html::Style::STYLE_TRANSFORM_ORIGIN_TOP){
                isXOrigin = false;
                return blink::Length(0, blink::LengthType::Percent);
            }else if(transformOrigin == Html::Style::STYLE_TRANSFORM_ORIGIN_BOTTOM){
                isXOrigin = false;
                return blink::Length(100, blink::LengthType::Percent);
            }
            return StyleParser::parseStringToLengthUnit(transformOrigin);
        }

        void parseTransformOrigin(blink::RenderStyle* renderStyle, const std::string& transformOrigin){
            std::vector<std::string> tokens = StyleParser::parserTokenBySpace(transformOrigin);
            if(tokens.size() == 1){
                bool isXOrigin = true;
                blink::Length length = parseTransformOriginToLength(tokens.at(0), isXOrigin);
                if(isXOrigin){
                   renderStyle->setTransformOriginX(length);
                }else{
                    renderStyle->setTransformOriginY(length);
                }
            }else if(tokens.size() == 2){
                bool isXOrigin = true;
                blink::Length length = parseTransformOriginToLength(tokens.at(0), isXOrigin);
                if(isXOrigin){
                    renderStyle->setTransformOriginX(length);
                    renderStyle->setTransformOriginY(parseTransformOriginToLength(tokens.at(1), isXOrigin));
                }else{
                    renderStyle->setTransformOriginY(length);
                    renderStyle->setTransformOriginX(parseTransformOriginToLength(tokens.at(1), isXOrigin));
                }
            }else if(tokens.size() == 3){
                bool isXOrigin = true;
                blink::Length length = parseTransformOriginToLength(tokens.at(0), isXOrigin);
                if(isXOrigin){
                    renderStyle->setTransformOriginX(length);
                    renderStyle->setTransformOriginY(parseTransformOriginToLength(tokens.at(1), isXOrigin));
                }else{
                    renderStyle->setTransformOriginY(length);
                    renderStyle->setTransformOriginX(parseTransformOriginToLength(tokens.at(1), isXOrigin));
                }
                renderStyle->setTransformOriginZ(StyleParser::parseStringByViewPortUnit(tokens.at(2)));
                renderStyle->setPerspective(StyleParser::parseStringByViewPortUnit(tokens.at(2)));
            }
        }


        void parseTransformStyle(blink::RenderStyle* renderStyle, const std::string& transformStyle){
            if(transformStyle == Html::Style::STYLE_TRANSFORM_STYLE_FLAT){
               renderStyle->setTransformStyle3D(blink::ETransformStyle3D::TransformStyle3DFlat);
            }else if(transformStyle == Html::Style::STYLE_TRANSFORM_STYLE_PRESERVE_3D){
               renderStyle->setTransformStyle3D(blink::ETransformStyle3D::TransformStyle3DPreserve3D);
            }
        }
    }
}