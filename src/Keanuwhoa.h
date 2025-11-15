#ifndef KEANUWHOA_H
#define KEANUWHOA_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <pplx/pplx.h>
#include <iostream>
#include <string>
#include <map>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Keanuwhoa {
private:
    std::string api_base = "https://whoa.onrender.com";
    http_client_config client_config;
    
    http_request create_request(const std::string& path, method m, const std::string& body_data = "", const std::string& content_type = "") {
        http_request request(m);
        
        // Полный набор браузерных заголовков
        request.headers().add("Accept", "application/json");
        request.headers().add("Content-Type", "application/json"); 
        request.headers().add("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/115.0");
        
        // Устанавливаем тело запроса, если передано
        if (!body_data.empty() && !content_type.empty()) {
            request.set_body(body_data, utility::conversions::to_string_t(content_type));
        }
        
        request.set_request_uri(utility::conversions::to_string_t(path));
        return request;
    }

    std::string build_query_params(const std::map<std::string, std::string>& params) {
        if (params.empty()) return "";
        
        std::string query = "?";
        bool first = true;
        for (const auto& param : params) {
            if (!param.second.empty()) {
                if (!first) query += "&";
                query += param.first + "=" + param.second;
                first = false;
            }
        }
        return query;
    }

public:
    Keanuwhoa() {
        client_config.set_validate_certificates(false);
    }

    pplx::task<json::value> random_whoas(int whoa_in_movie=0,int results=0,const std::string& sort="",const std::string& direction="",int year=0,const std::string& movie="",const std::string& director="") {
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::map<std::string, std::string> params;
        bool first_param = true;
        if (whoa_in_movie!=0) params["whoa_in_movie"] = std::to_string(whoa_in_movie);
        if (results!=0) params["results"] = std::to_string(results);
        if (!sort.empty()) params["sort"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(sort)));
        if (!direction.empty()) params["direction"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(direction)));
        if (!movie.empty()) params["movie"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(movie)));
        if (!director.empty()) params["director"] = utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(director)));
        std::string path = "/whoas/random";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> ordered_whoas(const std::string& ordered) {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/whoas/ordered/" + utility::conversions::to_utf8string(web::uri::encode_data_string(utility::conversions::to_string_t(ordered)));
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> movies_whoas() {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/whoas/movies";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }

    pplx::task<json::value> whoas_directors() {
        
        http_client client(utility::conversions::to_string_t(api_base), client_config);
        std::string path = "/whoas/directors";
        auto request = create_request(path, methods::GET);
        
        return client.request(request)
            .then([](http_response response) {
                if (response.status_code() == status_codes::OK) {
                    return response.extract_json();
                } else {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("HTTP Error: " + std::to_string(response.status_code())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return pplx::task_from_result(error_obj);
                }
            })
            .then([](pplx::task<json::value> previousTask) {
                try {
                    return previousTask.get();
                } catch (const std::exception& e) {
                    json::value error_obj;
                    error_obj[U("error")] = json::value::string(
                        U("Exception: " + std::string(e.what())));
                    error_obj[U("success")] = json::value::boolean(false);
                    return error_obj;
                }
            });
    }
};

#endif
