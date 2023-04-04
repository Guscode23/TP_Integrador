package com.proyecto.carrito.model;

import java.util.Date;
import java.util.List;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;

@Entity
@Table(name="transacciones")

public class Transaccion {
	@Id
	@GeneratedValue(strategy= GenerationType.IDENTITY)
     private Integer id;
     private String numero;
     private String usuario; // estaba pidiendo propiedad usuario
     private Date fechaCreacion;
     private Date fechaRecibida;
     private String Mediopago;
     
     private double total;
     
     @ManyToOne
     private Cliente cliente;
     
     @OneToMany(mappedBy="transaccion")
     private List<DetalleOrden>detalle;
     
     //Constructor//
     
     public Transaccion() {
       }
     
     public Transaccion(Integer id, String numero, Date fechaCreacion, Date fechaRecibida, String mediopago,
			double total) {
		super();
		this.id = id;
		this.numero = numero;
		this.fechaCreacion = fechaCreacion;
		this.fechaRecibida = fechaRecibida;
		Mediopago = mediopago;
		this.total = total;
	}





	//Getters and Setters//
     
     public Integer getId() {
		return id;
	}


	public void setId(Integer id) {
		this.id = id;
	}


	public String getNumero() {
		return numero;
	}


	public void setNumero(String numero) {
		this.numero = numero;
	}


	public Date getFechaCreacion() {
		return fechaCreacion;
	}


	public void setFechaCreacion(Date fechaCreacion) {
		this.fechaCreacion = fechaCreacion;
	}


	public Date getFechaRecibida() {
		return fechaRecibida;
	}


	public void setFechaRecibida(Date fechaRecibida) {
		this.fechaRecibida = fechaRecibida;
	}


	public double getTotal() {
		return total;
	}


	public void setTotal(double total) {
		this.total = total;
	}
    
	public String getMediopago() {
		return Mediopago;
	}


	public void setMediopago(String mediopago) {
		Mediopago = mediopago;
	}

	public Cliente getCliente() {
		return cliente;
	}

	public void setCliente(Cliente cliente) {
		this.cliente = cliente;
	}

	
	
     
	//Metodo para mostrar por consola//
     
	
	public List<DetalleOrden> getDetalle() {
		return detalle;
	}

	public void setDetalle(List<DetalleOrden> detalle) {
		this.detalle = detalle;
	}

	@Override
	public String toString() {
		return "Transaccion [id=" + id + ", numero=" + numero + ", fechaCreacion=" + fechaCreacion + ", fechaRecibida="
				+ fechaRecibida + ", Mediopago=" + Mediopago + ", total=" + total + "]";
	}
    	
     
     
     
     
     
	
	
	
}
