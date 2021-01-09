using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Books_CRUD.Models
{
    public class Publisher
    {
        public int PublisherId { get; set; }
        public String Name { get; set; }

        [Required]
        public virtual ContactInfo ContactInfo { get; set; }
        public virtual ICollection<Book> Books { get; set; }
    }
}