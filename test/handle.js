function getFile(url){
    return $.ajax(
	      {
		        type     : 'GET',
		        url      : url,
		        timeout  : 20000,
		        cache    : false,
	      });
}

function getJson(){
    return $.ajax(
	      {
		        type     : 'GET',
		        url      : 'https://raw.githubusercontent.com/beet-aizu/library/master/test/list.json',
		        dataType : 'json',
		        timeout  : 20000,
		        cache    : false,
	      });
}

// copied from https://iwb.jp/jquery-javascript-html-escape/
const htmlEscape = (str) => {
    if (!str) return;
    return str.replace(/[<>&"'`]/g, (match) => {
        const escape = {
            '<': '&lt;',
            '>': '&gt;',
            '&': '&amp;',
            '"': '&quot;',
            "'": '&#39;',
            '`': '&#x60;'
        };
        return escape[match];
    });
}

function a_tag(f){
    return $('<a>').attr({href: 'status.html?url=' + f}).html(f);
}

function show_top(){
    $('#top').html($('<h1>').text('Verification Status'));
    $('<button>').attr({type: "button", id: "unverified"})
        .text('Show Only Unverified').appendTo('#list');

    $('#unverified').on('click',function(){
        getJson().done(function(data){
            $('#list').html('');

            $('<button>').attr({type: "button", id: "reloader"})
                .text('Reset').appendTo('#list');

            $('#reloader').on('click',function(){
                location.reload();
            });

            for(f of data.library){
                if(!data[f]){
                    $('#list').append($('<ul>').append(a_tag(f)));
                }
            }
        });
    });

    getJson().done(function(data){
        console.log(data);
        for(f of data.library){
            var list = $('<ul>');

            list.append(a_tag(f));

            if(data[f]){
                $.each(data[f], function(_, g){
                    list.append($('<li>').text('-> ').append(a_tag(g)));
                });
            }

            list.appendTo('#list');
        }
    });
}

function list_dependency(url, arrow){
    var list = $('<ul>');
    list.append($('<h2>').text('Dependency'));
    getJson().done(function(data){
        $.each(data[url], function(_, g){
            list.append($('<li>').text(arrow).append(a_tag(g)));
        });
        list.appendTo('#dependency');
    });
    $('#dependency').html(list);
}

function show_library(url, data){
    $('#top').html($('<h1>').text(url));

    list_dependency(url, '-> ');

    data = htmlEscape(data);
    l = data.search("BEGIN CUT HERE") + 15;
    r = data.search(/\n[^\n]*END CUT HERE/);
    data = data.substr(l, r - l);
    data = '<!-- LIBRARY --><pre><code>' + data + '</code></pre>';
    $('#status').html(data);
}

function get_problem_url(data){
    return /#define PROBLEM \"(.*)\"/.exec(data)[1];
}

function show_test(url, data){
    $('#top').html($('<h1>').text(url));

    list_dependency(url, '<- ');

    $('#problem').html($('<a>')
                       .attr({href: get_problem_url(data)})
                       .text('Problem Statement'));

    data = htmlEscape(data);
    data = '<!-- TEST --><pre><code>' + data + '</code></pre>';
    $('#status').html(data);
}

function show_content(url){
    var github = 'https://github.com/beet-aizu/library/blob/master';
    $('#github').html($('<a>')
                      .attr({href: github + url})
                      .text('View on GitHub'));

    var path = 'https://beet-aizu.github.io/library' + url;
    getFile(path).done(function(data){
        if(url.search(/.*\.test\.cpp$/) < 0){
            show_library(url, data);
        }else{
            show_test(url, data);
        }
    });
}

$(document).ready(function(){
    $('#top').click(function(){
        window.location.href = 'status.html';
    });

    var query = window.location.search.substring(1);
    if(query.length == 0) {
        show_top();
    }else{
        var url = decodeURIComponent(query.split('&')[0].split('=')[1]);
        show_content(url);
    }
});
