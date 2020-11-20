using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using WebApi.Models;

namespace WebApi.Areas.HelpPage.Controllers
{
    public class BooksController : ApiController
    {
        private DbCtx ctx = new DbCtx();

        public List<Book> Get()
        {
            return ctx.Books.ToList();
        }

        public IHttpActionResult Get(int id)
        {
            Book book = ctx.Books.Find(id);
            
            if(book == null)
            {
                //returneaza codul 404
                return NotFound();
            }
            //returneaza codul de succes 200
            //in body vor fi memorate datele obiectului book
            return Ok(book);
        }

        //cand facem post nu e nevoie sa dam bookId. Se incrementeaza automat
        public IHttpActionResult Post([FromBody] Book book)
        {
            //adaugam cartea din parametru
            ctx.Books.Add(book);
            ctx.SaveChanges();

            //facem un url care sa ne redirectioneze la default api si returneaza si cartea
            var url = new Uri(Url.Link("DefaultApi", new { id = book.BookId }));
            return Created(url, book);
        }

        public IHttpActionResult Put(int id, [FromBody] Book b)
        {
            Book book = ctx.Books.Find(id);

            if(book == null)
            {
                return NotFound();
            }
            //modificam cartea veche cu valorile noi
            book.Title = b.Title;
            book.Author = b.Author;
            ctx.SaveChanges();
            return Ok(book);
        }

        public IHttpActionResult Delete(int id)
        {
            Book book = ctx.Books.Find(id);
            
            if(book == null)
            {
                return NotFound();
            }

            ctx.Books.Remove(book);
            ctx.SaveChanges();
            return Ok(book);
        }
    }
}
